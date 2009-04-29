/*
 *  GPhy.h
 *  GarminKit
 *
 *  Created by Jon Nall on 10/16/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */
#include <inttypes.h>

@protocol GPhy <NSObject>
-(bool)initialize;
-(void)sendPacket:(uint8_t) pktID withData:(NSData*) data;
-(NSData*)recvPacket;

@end
