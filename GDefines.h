#ifndef __GDEFINES_H__
#define __GDEFINES_H__

/*
 *  GDefines.h
 *  GarminKit
 *
 *  Created by Jon Nall on 11/2/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "GSymbolDefines.h"

typedef UInt16 Records_Type;
typedef UInt16 Command_Id_Type;
typedef UInt32 time_type;

typedef struct 
{ 
	UInt16 product_ID; 
	SInt16 software_version; 
	char product_description[];  // null-terminated string(s)
} Product_Data_Type; 

// Variable length string
/*
typedef struct 
{ 
	char ext_product_description[]; // null-terminated string(s)
} Ext_Product_Data_Type; 
*/

typedef struct 
{ 
	UInt8 tag; 
	UInt16 data; 
} Protocol_Data_Type; 

typedef Protocol_Data_Type Protocol_Array_Type[];

typedef struct 
{ 
	SInt32 lat; /* latitude in semicircles */ 
	SInt32 lon; /* longitude in semicircles */ 
} position_type; 

typedef struct 
{ 
	Float64 lat; /* latitude in radians */ 
	Float64 lon; /* longitude in radians */ 
} radian_position_type; 

#include "GDataStructures.h"

#endif // __GDEFINES_H__
