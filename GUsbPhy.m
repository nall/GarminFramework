//
//  GUsbPhy.m
//  GarminKit
//
//  Created by Jon Nall on 10/16/06.
//  Copyright 2006 __MyCompanyName__. All rights reserved.
//

#import "GUsbPhy.h"
#include <IOKit/IOKitLib.h>
#include <IOKit/IOCFPlugIn.h>
#include <IOKit/usb/IOUSBLib.h>

const SInt32 GARMIN_VENDOR = 0x091E;
const SInt32 GARMIN_DEVICE = 0x0003;
const UInt8 GARMIN_INPUT_PIPE_INTR = 1;
const UInt8 GARMIN_OUTPUT_PIPE_BULK = 2;
const UInt8 GARMIN_INPUT_PIPE_BULK = 3;

void readCallback(void* refcon, IOReturn result, void* arg)
{
    printf("Async read COMPLETE!!!\n");
    NSLog(@"In readCallback. refcon: %p; result: %d, arg:%p", refcon, result, arg);
}

@implementation GUsbPhy
-(id)init
{
    self = [super init];
    if(self != 0)
    {
        myIntf = 0;
        myDev = 0;
    }
    
    return self;
}

-(void)dealloc
{
    NSLog(@"GUSBPhy::dealloc");
    if(myIntf != 0)
    {
        NSLog(@"Closing USB Interface");
        (*myIntf)->USBInterfaceClose(myIntf);
        (*myIntf)->Release(myIntf);
        myIntf = 0;
    }
    if(myDev != 0)
    {
        NSLog(@"Closing USB Device");
        (*myDev)->USBDeviceClose(myDev);
        (*myDev)->Release(myDev);
        myDev = 0;
    }
    [super dealloc];
}

-(bool)initialize
{
	// Setup OS USB structures, etc
	if([self osxInit] == false) return false;

	// Handshake the product information
    //
	// Send Pid_Start_Session
	UInt8 pkt[13] = {0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0};
    NSData* data = [[NSData alloc] initWithBytes:&(pkt[0]) length:13];
    [self sendPacket:0x33 withData:data];
	data = [self recvPacket];
	
	UInt32 length = 0;
	bool rc = false;
	rc = [self verifyPacketAndGetLength:data withType:0 withPacketID:6 getLength:&length];
	if(!rc) return false;
	
	UInt8 pkt2[13] = {20, 0, 0, 0, 254, 0, 0, 0, 0, 0, 0, 0, 0};
    data = [[NSData alloc] initWithBytes:&(pkt2[0]) length:13];
    [self sendPacket:0x33 withData:data];

	// Receive Pid_Product_Data
	data = [self recvPacket];	
	rc = [self verifyPacketAndGetLength:data withType:20 withPacketID:255 getLength:&length];
	if(!rc) return false;
	
	{
		NSRange range = {14, [data length] - 14};
		char* cString = (char*)[[data subdataWithRange: range] bytes];
		NSString* infoString = [NSString stringWithCString:cString encoding: NSASCIIStringEncoding];
		NSLog(@"Product Info: \"%@\"", infoString);
	}
	
	// Receive Pid_Ext_Product_Data
	data = [self recvPacket];	
	rc = [self verifyPacketAndGetLength:data withType:20 withPacketID:248 getLength:&length];
	if(!rc) return false;

	// Receive Protocol Capability Protocol
	data = [self recvPacket];	
	rc = [self verifyPacketAndGetLength:data withType:20 withPacketID:253 getLength:&length];
	if(!rc) return false;

	UInt8 extBytes = length - [data length] + 12;
	while(extBytes > 0)
	{
		// Receive more Pid_Ext_Product_Data
		data = [self recvPacket];
		extBytes -= [data length];
	}
	
	return true;
}

-(void)sendPacket:(UInt8) pktID withData:(NSData*) data
{
    // NSLog(@"GUsbPhy::sendPacket(%d) [%d bytes]", pktID, [data length]);
    if(myIntf == 0)
    {
        NSLog(@"No valid interface available");
        return;
    }
    
    void* buf = malloc([data length]);
    memcpy(buf, [data bytes], [data length]);
    // NSLog(@"Writing pkt: %@", data);
    IOReturn err = (*myIntf)->WritePipe(myIntf, GARMIN_OUTPUT_PIPE_BULK,
                                        buf, [data length]);
    free(buf);
    if(err)
    {
        NSLog(@"Error writing bytes to interface");
    }
}

-(NSData*)recvPacket
{
    static int foo = 16;
    
//    NSLog(@"GUsbPhy::recvPacket");
    if(myIntf == 0)
    {
        NSLog(@"No valid interface available");
        return 0;
    }
    
    UInt32 size = foo;
    foo = 64;
    void* buf = malloc(size);
    bzero(buf, size);
    IOReturn err = (*myIntf)->ReadPipe(myIntf, GARMIN_INPUT_PIPE_INTR, buf, &size);

    if(err)
    {
        NSLog(@"ERROR!! 0x%x", err);
        free(buf);
        return 0;
    }
    
    NSData* data = [[NSData alloc] initWithBytes:buf length:size];
    // NSLog(@"Read %d bytes: %@", size, data);
    
    free(buf);
    return data;
}

-(bool)verifyPacketAndGetLength: (NSData*) pkt withType: (UInt8) type withPacketID: (UInt16) packetID getLength: (UInt32*) length
{
	UInt8* bytes = (UInt8*) [pkt bytes];
	if(bytes[0] != type)
	{
		NSLog(@"ERROR: Expected Packet Type 0x%x, but observed 0x%x", type, bytes[0]);
		return false;
	}
	
	UInt16 observedID = bytes[5];
	observedID <<= 8;
	observedID |= bytes[4];
	if(observedID != packetID)
	{
		NSLog(@"ERROR: Expected PacketID 0x%x, but observed 0x%x", packetID, observedID);
		return false;
	}
	
	UInt32 len = 0;
	for(UInt8 i = 11; i >= 8; --i)
	{
		len <<= 8;
		len |= bytes[i];
	}
	
	*length = len;
	
	return true;
}

-(bool)initGarminDevice:(io_service_t) usbDevRef
{
    SInt32 score = 0;
    IOCFPlugInInterface** ioDev = 0;
    IOUSBDeviceInterface** dev;
    IOReturn err = IOCreatePlugInInterfaceForService(usbDevRef,
                                                     kIOUSBDeviceUserClientTypeID,
                                                     kIOCFPlugInInterfaceID,
                                                     &ioDev, &score);
    if(err || !ioDev) return false;
    
    err = (*ioDev)->QueryInterface(ioDev, CFUUIDGetUUIDBytes(kIOUSBDeviceInterfaceID),
                                   (LPVOID)&dev);
    if(err || !dev) return false;
    
    err = (*dev)->USBDeviceOpen(dev);
    if(err) return false;
		    
			
	
    // Set the device to use the default config
    IOUSBConfigurationDescriptorPtr	confDescr;
    err = (*dev)->GetConfigurationDescriptorPtr(dev, 0, &confDescr);
    if(err)
    {
        (*dev)->USBDeviceClose(dev);
        (*dev)->Release(dev);
        return false;
    }
    
    err = (*dev)->SetConfiguration(dev, confDescr->bConfigurationValue);
    if(err)
    {
        (*dev)->USBDeviceClose(dev);
        (*dev)->Release(dev);
        return false;
    }
    
    // Get the only interface
    IOUSBFindInterfaceRequest interfaceRequest;
    interfaceRequest.bInterfaceClass = kIOUSBFindInterfaceDontCare;
    interfaceRequest.bInterfaceSubClass = kIOUSBFindInterfaceDontCare;
    interfaceRequest.bInterfaceProtocol = kIOUSBFindInterfaceDontCare;
    interfaceRequest.bAlternateSetting = kIOUSBFindInterfaceDontCare;
    
    io_iterator_t iterator = 0;
    err = (*dev)->CreateInterfaceIterator(dev, &interfaceRequest, &iterator);
    if(err)
    {
        (*dev)->USBDeviceClose(dev);
        (*dev)->Release(dev);
        return false;
    }
    
    io_service_t usbIntfRef;
    bool foundIntf = false;
    while(!foundIntf && (usbIntfRef = IOIteratorNext(iterator)))
    {
        NSLog(@"Found Interface: %p", usbIntfRef);
        foundIntf = [self initGarminInterface:usbIntfRef];
        IOObjectRelease(usbIntfRef);
    }
    IOObjectRelease(iterator);
    iterator = 0;
    
    if(foundIntf)
    {
        myDev = dev;
    }
    else
    {
        (*dev)->USBDeviceClose(dev);
        (*dev)->Release(dev);
    }

    return foundIntf;
}

-(bool)initGarminInterface:(io_service_t)usbIntfRef
{
    // Verify that we have 3 endpoints. If so, save the Interface and return
    // true. Else return false
    // 1: IN Interrupt
    // 2: IN BULK
    // 3: OUT BULK

    SInt32 score;
    IOCFPlugInInterface** ioDev;
    IOReturn err = IOCreatePlugInInterfaceForService(usbIntfRef,
                                                     kIOUSBInterfaceUserClientTypeID,
                                                     kIOCFPlugInInterfaceID,
                                                     &ioDev,
                                                     &score);
    if(err) return false;
    
    IOUSBInterfaceInterface** intf = 0;
    err = (*ioDev)->QueryInterface(ioDev, 
                                   CFUUIDGetUUIDBytes(kIOUSBInterfaceInterfaceID),
                                   (LPVOID)&intf);
	IODestroyPlugInInterface(ioDev);
    if(err || !intf) return false;
    
    err = (*intf)->USBInterfaceOpen(intf);
    if(err) return false;
    
    // A Garmin Device has 3 pipes:
    // 1: IN INTERRUPT
    // 2: IN BULK
    // 3: OUT BULK
    // If these aren't in place, return false. Otherwise, we're good.
    UInt8 numPipes = 0;
    err = (*intf)->GetNumEndpoints(intf, &numPipes);
    if(err || (numPipes != 3)) 
    {
        (*intf)->USBInterfaceClose(intf);
        (*intf)->Release(intf);
        return false;
    }

    UInt8 directions[4] = {0, kUSBIn, kUSBOut, kUSBIn};
    UInt8 xferTypes[4] =  {0, kUSBInterrupt, kUSBBulk, kUSBBulk};    
    for(int i = 1; i <= numPipes; ++i)
    {
        UInt8 direction = 0;
        UInt8 number = 0;
        UInt8 xferType = 0;
        UInt8 interval = 0;
        UInt16 maxPktSize = 0;
        err = (*intf)->GetPipeProperties(intf, i, &direction, &number, &xferType,
                                         &maxPktSize, &interval);
        const bool dirOK = direction == directions[i];
        const bool typeOK = xferType == xferTypes[i];
        if(err || !dirOK || !typeOK)
        {
            NSLog(@"Couldn't validate endpoint %d. err = %d; dirOK = %d, typeOK = %d",
                  i, err, dirOK, typeOK);
            (*intf)->USBInterfaceClose(intf);
            (*intf)->Release(intf);            
            return false;        
        }        
    }
    
    CFRunLoopSourceRef runLoopSource;
    err = (*intf)->CreateInterfaceAsyncEventSource(intf, &runLoopSource);
    if (err)
    {
        printf("unable to create async event source (%08x)\n", err);
        (*intf)->USBInterfaceClose(intf);
        (*intf)->Release(intf);
        return false;
    }
    CFRunLoopAddSource(CFRunLoopGetCurrent(), runLoopSource, kCFRunLoopDefaultMode);
    printf("Async event source added to run loop.\n");

    
    myIntf = intf;
    return true;
}

-(bool)osxInit
{
    NSLog(@"GUsbPhy::initialize");
	
    mach_port_t masterPort = 0;
    kern_return_t err = IOMasterPort(MACH_PORT_NULL, &masterPort);
    if(err)
    {
        return false;
    }
    
    CFMutableDictionaryRef matchingDict = IOServiceMatching(kIOUSBDeviceClassName);
    if(!matchingDict)
    {
		mach_port_deallocate(mach_task_self(), masterPort);
        return false;
    }
    
    CFNumberRef numberRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type,
                                           &GARMIN_VENDOR);
    if(!numberRef)
    {
	    mach_port_deallocate(mach_task_self(), masterPort);
        return false;
    }
    
    CFDictionaryAddValue(matchingDict, CFSTR(kUSBVendorID), numberRef);
    CFRelease(numberRef);
    numberRef = 0;
    
    numberRef = CFNumberCreate(kCFAllocatorDefault,kCFNumberSInt32Type,&GARMIN_DEVICE);
    if(!numberRef)
    {
        return false;
    }
    CFDictionaryAddValue(matchingDict,CFSTR(kUSBProductID),numberRef);
    CFRelease(numberRef);
    numberRef = 0;
    
    io_iterator_t iterator = 0;
    err = IOServiceGetMatchingServices(masterPort, matchingDict, &iterator);
    matchingDict = 0;
    
    io_service_t usbDeviceRef;
    bool foundDev = false;
    while(!foundDev && (usbDeviceRef = IOIteratorNext(iterator)))
    {
        NSLog(@"Found Device: %p", usbDeviceRef);
        foundDev = [self initGarminDevice:usbDeviceRef];        
        IOObjectRelease(usbDeviceRef);
    }
    
    IOObjectRelease(iterator);
    iterator = 0;
    
    mach_port_deallocate(mach_task_self(), masterPort);
    
    return foundDev;
}


@end


