//
//  BaseIOTest.m
//  GarminKit
//
//  Created by Jon Nall on 10/13/06.
//  Copyright 2006 __MyCompanyName__. All rights reserved.
//
#include "GUsbPhy.h"
#include <unistd.h>

typedef struct 
{ 
	struct 
	{ 
		struct 
		{ 
			uint8 low_heart_rate; /* In beats-per-minute, must be > 0 */ 
			uint8 high_heart_rate; /* In beats-per-minute, must be > 0 */ 
			uint16 unused;  /* Unused. Set to 0. */ 
		} heart_rate_zones[5]; 
		struct 
		{ 
			float low_speed;  /* In meters-per-second */ 
			float high_speed;  /* In meters-per-second */ 
			char name[16];  /* Null-terminated speed-zone name */ 
		} speed_zones[10]; 
		float gear_weight;  /* Weight of equipment in kilograms */ 
		uint8 max_heart_rate; /* In beats-per-minute, must be > 0 */ 
		uint8 unused1;  /* Unused. Set to 0. */ 
		uint16 unused2;  /* Unused. Set to 0. */ 
	} activities[3]; 
	float weight;  /* User’s weight, in kilograms */ 
	uint16 birth_year;  /* No base value (i.e. 1990 means 1990) */ 
	uint8 birth_month;  /* 1 = January, etc. */ 
	uint8 birth_day;  /* 1 = first day of month, etc. */ 
	uint8 gender;  /* See below */ 
} D1004_Fitness_User_Profile_Type; 


int main(int argc, char** argv)
{
	NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];

    id<GPhy> phy = [GUsbPhy new];
    bool status = [phy initialize];
    NSLog(@"Initialize status: %d", status);
	
	NSLog(@"Get Fitness Profile");

	UInt8 pkt[14] = {20, 0, 0, 0,
					 10, 0, 0, 0,
					 2, 0, 0, 0, 
					 0xC5, 1};
    NSData* data = [[NSData alloc] initWithBytes:&(pkt[0]) length:14];
    [phy sendPacket:0x33 withData:data];
	data = [phy recvPacket];
	
	UInt32 length = 0;
	bool rc = false;
	rc = [phy verifyPacketAndGetLength:data withType:20 withPacketID:993 getLength:&length];
	if(!rc) return 1;
	NSLog(@"Expecting to find %d bytes (+12 header bytes)", length);

	NSMutableData* profileData = [NSMutableData dataWithLength:0];
	NSRange range = {12, [data length] - 12};
	[profileData appendData: [data subdataWithRange: range]];

	UInt8 extBytes = length - [data length] + 12;
	while(extBytes > 0)
	{
		// Receive more Pid_Ext_Product_Data
		data = [phy recvPacket];
		extBytes -= [data length];
		[profileData appendData: data];
	}

	D1004_Fitness_User_Profile_Type profile;
	memcpy(&profile, [profileData bytes], [profileData length]);
	
	for(int a = 0; a < 3; ++a)
	{
		switch(a)
		{
			case 0:
				NSLog(@"Running"); break;
			case 1:
				NSLog(@"Cycling"); break;
			case 2:
				NSLog(@"Other"); break;
			default:
				NSLog(@"ERROR!!"); break;
		};
		NSLog(@"\tMax Heart Rate: %d", profile.activities[a].max_heart_rate);
		NSLog(@"\tGear Weight: %f", profile.activities[a].gear_weight);
		for(int hrz = 0; hrz < 5; ++hrz)
		{
			NSLog(@"\tHeartRateZone[%d]: Low: %d, High %d", hrz, profile.activities[a].heart_rate_zones[hrz].low_heart_rate, profile.activities[a].heart_rate_zones[hrz].high_heart_rate);
		}
		for(int sz = 0; sz < 10; ++sz)
		{
			NSLog(@"\tSpeedZone[%d]: [%s] Low: %f, High %f", sz, profile.activities[a].speed_zones[sz].name, profile.activities[a].speed_zones[sz].low_speed, profile.activities[a].speed_zones[sz].high_speed);
		}
	}
	NSLog(@"Weight: %f (kg)", profile.weight);
	NSLog(@"Birthday: %d/%d/%d", profile.birth_month, profile.birth_day, profile.birth_year);
	NSLog(@"Gender: %s", (profile.gender == 0) ? "Female" : "Male");
	
    [phy release];
	
	[pool release];
    return 0;
}