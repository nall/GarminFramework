//
//  GUsbPhy.h
//  GarminKit
//
//  Created by Jon Nall on 10/16/06.
//  Copyright 2006 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "GPhy.h"
#include "GUsbDefines.h"

#include <mach/mach.h>
#include <IOKit/usb/IOUSBLib.h>

@interface GUsbPhy : NSObject<GPhy>
{
    @private IOUSBDeviceInterface** myDev;
    @private IOUSBInterfaceInterface** myIntf;
}

-(bool)initialize;
-(void)sendPacket:(uint8_t) pktID withData:(NSData*) data;
-(NSData*)recvPacket;

-(bool)initGarminDevice:(io_service_t)usbDevRef;
-(bool)initGarminInterface:(io_service_t)usbIntfRef;

// Private Methods
-(bool)osxInit;
-(bool)verifyPacketAndGetLength: (NSData*) pkt withType: (UInt8) type withPacketID: (UInt16) packetID getLength: (UInt32*) length;
@end
