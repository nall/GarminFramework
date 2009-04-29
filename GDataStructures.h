#ifndef __GDATASTRUCTURES_H__
#define __GDATASTRUCTURES_H__

/*
 *  GDataStructures.h
 *  GarminKit
 *
 *  Created by Jon Nall on 11/2/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "GDefines.h"

typedef struct 
{ 
	char ident[6];		/* identifier */ 
	position_type posn; /* position */ 
	UInt32  unused;		/* should be set to zero */ 
	char cmnt[40];		/* comment */
} D100_Wpt_Type; 

typedef struct 
{ 
	char ident[6];		/* identifier */ 
	position_type posn; /* position */ 
	UInt32 unused;		/* should be set to zero */ 
	char cmnt[40];		/* comment */ 
	Float32 dst;		/* proximity distance (meters) */ 
	UInt8 smbl;			/* symbol id */ 
} D101_Wpt_Type; 

typedef struct 
{ 
	char ident[6];		/* identifier */ 
	position_type posn; /* position */ 
	uint32 unused;		/* should be set to zero */ 
	char cmnt[40];		/* comment */ 
	Float32 dst;		/* proximity distance (meters) */ 
	symbol_type smbl;	/* symbol id */ 
} D102_Wpt_Type; 

typedef struct 
{ 
	char ident[6];		/* identifier */ 
	position_type posn; /* position */ 
	UInt32 unused;		/* should be set to zero */ 
	char cmnt[40];		/* comment */ 
	UInt8 smbl;			/* symbol id */ 
	UInt8 dspl;			/* display option */ 
} D103_Wpt_Type; 

enum D103DSymbolType
{ 
	smbl_dot =  0,			/* dot symbol */ 
	smbl_house =  1,		/* house symbol */ 
	smbl_gas =  2,			/* gas symbol */ 
	smbl_car =  3,			/* car symbol */ 
	smbl_fish =  4,			/* fish symbol */ 
	smbl_boat =  5,			/* boat symbol */ 
	smbl_anchor =  6,		/* anchor symbol */ 
	smbl_wreck =  7,		/* wreck symbol */ 
	smbl_exit =  8,			/* exit symbol */ 
	smbl_skull =  9,		/* skull symbol */ 
	smbl_flag = 10,			/* flag symbol */ 
	smbl_camp = 11,			/* camp symbol */ 
	smbl_circle_x = 12,		/* circle with x symbol */ 
	smbl_deer = 13,			/* deer symbol */ 
	smbl_1st_aid = 14,		/* first aid symbol */ 
	smbl_back_track = 15	/* back track symbol */ 
}; 	

enum D103DisplayOption
{ 
	dspl_name = 0,	/* Display symbol with waypoint name */ 
	dspl_none = 1,	/* Display symbol by itself */ 
	dspl_cmnt = 2	/* Display symbol with comment */ 
};

typedef struct 
{ 
	char ident[6];		/* identifier */ 
	position_type posn; /* position */ 
	UInt32 unused;		/* should be set to zero */ 
	char cmnt[40];		/* comment */ 
	Float32 dst;		/* proximity distance (meters) */ 
	symbol_type smbl;	/* symbol id */ 
	UInt8 dspl;			/* display option */ 
} D104_Wpt_Type; 

enum D104DisplayOption
{ 
	dspl_smbl_none = 0, /* Display symbol by itself  */ 
	dspl_smbl_only = 1, /* Display symbol by itself  */ 
	dspl_smbl_name = 3, /* Display symbol with waypoint name */ 
	dspl_smbl_cmnt = 5, /* Display symbol with comment  */ 
}; 

typedef struct  
{ 
	position_type posn;		/* position */ 
	symbol_type smbl;		/* symbol id */
	char wpt_ident[];		/* null-terminated string */
} D105_Wpt_Type; 

typedef struct 
{ 
	UInt8 wpt_class;	/* class */ 
	UInt8 subclass[13]; /* subclass */ 
	position_type posn; /* position */ 
	symbol_type smbl;	/* symbol id */ 
	char strings[];
	/*
	char wpt_ident[]; 
	char lnk_ident[];
	*/
} D106_Wpt_Type; 

typedef struct 
{ 
	char ident[6];		/* identifier */ 
	position_type posn; /* position */ 
	UInt32 unused;		/* should be set to zero */ 
	char cmnt[40];		/* comment */ 
	UInt8 smbl;			/* symbol id */ 
	UInt8 dspl;			/* display option */ 
	Float32 dst;		/* proximity distance (meters) */ 
	UInt8 color;		/* waypoint color */ 
} D107_Wpt_Type; 

enum D107Color
{ 
	clr_default = 0,	/* Default waypoint color */ 
	clr_red = 1,		/* Red */ 
	clr_green = 2,		/* Green */ 
	clr_blue = 3		/* Blue */ 
}; 

typedef struct 
{ 
	UInt8 wpt_class; /* class (see below) */ 
	UInt8 color; /* color (see below) */ 
	UInt8 dspl; /* display options (see below) */ 
	UInt8 attr; /* attributes (see below) */ 
	symbol_type smbl; /* waypoint symbol */ 
	UInt8 subclass[18]; /* subclass */ 
	position_type posn; /* position */ 
	Float32 alt; /* altitude in meters */ 
	Float32 dpth; /* depth in meters */ 
	Float32 dist; /* proximity distance in meters */ 
	char state[2]; /* state */ 
	char cc[2]; /* country code */ 
	char strings[];
	/*
	char ident[];		// variable length string
	char comment[];		// waypoint user comment
	char facility[];	// facility name
	char city[];		// city name
	char addr[];		// address number
	char cross_road[];  // intersecting road label
	*/
} D108_Wpt_Type; 

enum D108WaypointClass
{ 
	user_wpt = 0x00, /* user waypoint */ 
	avtn_apt_wpt = 0x40, /* aviation airport waypoint */ 
	avtn_int_wpt = 0x41, /* aviation intersection waypoint */ 
	avtn_ndb_wpt = 0x42, /* aviation NDB waypoint */ 
	avtn_vor_wpt = 0x43, /* aviation VOR waypoint */ 
	avtn_arwy_wpt = 0x44, /* aviation airport runway waypoint */ 
	avtn_aint_wpt = 0x45, /* aviation airport intersection */ 
	avtn_andb_wpt = 0x46, /* aviation airport ndb waypoint */ 
	map_pnt_wpt = 0x80, /* map point waypoint */ 
	map_area_wpt = 0x81, /* map area waypoint */ 
	map_int_wpt = 0x82, /* map intersection waypoint */ 
	map_adrs_wpt = 0x83, /* map address waypoint */ 
	map_line_wpt = 0x84, /* map line waypoint */ 
}; 

enum D108Color
{ 
	clr_black = 0, 
	clr_dark_red = 1, 
	clr_dark_green = 2, 
	clr_dark_yellow = 3, 
	clr_dark_blue = 4, 
	clr_dark_magenta = 5, 
	clr_dark_cyan = 6, 
	clr_light_gray = 7, 
	clr_dark_gray = 8, 
	clr_red = 9, 
	clr_green = 10, 
	clr_yellow = 11, 
	clr_blue = 12, 
	clr_magenta = 13, 
	clr_cyan = 14, 
	clr_white = 15, 
	clr_default_color = 255 
}; 

typedef struct 
{ 
	UInt8 dtyp; /* data packet type (0x01 for D109) */ 
	UInt8 wpt_class; /* class */ 
	UInt8 dspl_color; /* display & color (see below) */ 
	UInt8 attr; /* attributes (0x70 for D109) */ 
	symbol_type smbl; /* waypoint symbol */ 
	UInt8 subclass[18]; /* subclass */ 
	position_type posn; /* position */ 
	Float32 alt; /* altitude in meters */ 
	Float32 dpth; /* depth in meters */ 
	Float32 dist; /* proximity distance in meters */ 
	char state[2]; /* state */ 
	char cc[2]; /* country code */ 
	UInt32 ete; /* outbound link ete in seconds */ 
	
	char strings[];
	
	/*
	char ident[];		// variable length string
	char comment[];     // waypoint user comment
	char facility[];    // facility name
	char city[];		// city name
	char addr[];		// address number
	char cross_road[];	// intersecting road label
	*/
} D109_Wpt_Type;

typedef struct 
{ 
	UInt8 dtyp; /* data packet type (0x01 for D110) */ 
	UInt8 wpt_class; /* class */ 
	UInt8 dspl_color; /* display & color (see below) */ 
	UInt8 attr; /* attributes (0x80 for D110) */ 
	symbol_type smbl; /* waypoint symbol */ 
	UInt8 subclass[18]; /* subclass */ 
	position_type posn; /* position */ 
	Float32 alt; /* altitude in meters */ 
	Float32 dpth; /* depth in meters */ 
	Float32 dist; /* proximity distance in meters */ 
	char state[2]; /* state */ 
	char cc[2]; /* country code */ 
	UInt32 ete; /* outbound link ete in seconds */ 
	Float32 temp; /* temperature */ 
	time_type time; /* timestamp */ 
	UInt16 wpt_cat; /* category membership */ 
	
	char strings[];
	/*
	char ident[];		// variable length string
	char comment[];		// waypoint user comment
	char facility[];	// facility name
	char city[];		// city name
	char addr[];		// address number
	char cross_road[];	//intersecting road label
	*/
} D110_Wpt_Type; 

enum D110WaypointClass
{ 
	user_wpt = 0x00, /* user waypoint */ 
	avtn_apt_wpt = 0x40, /* aviation airport waypoint */ 
	avtn_int_wpt = 0x41, /* aviation intersection waypoint */ 
	avtn_ndb_wpt = 0x42, /* aviation NDB waypoint */ 
	avtn_vor_wpt = 0x43, /* aviation VOR waypoint */ 
	avtn_arwy_wpt = 0x44, /* aviation airport runway waypoint */ 
	avtn_aint_wpt = 0x45, /* aviation airport intersection */ 
	avtn_andb_wpt = 0x46, /* aviation airport ndb waypoint */ 
	map_pnt_wpt = 0x80, /* map point waypoint */ 
	map_area_wpt = 0x81, /* map area waypoint */ 
	map_int_wpt = 0x82, /* map intersection waypoint */ 
	map_adrs_wpt = 0x83, /* map address waypoint */ 
	map_line_wpt = 0x84, /* map line waypoint */ 
}; 

enum D110Color
{ 
	clr_Black = 0,  
	clr_Dark_Red = 1, 
	clr_Dark_Green = 2, 
	clr_Dark_Yellow = 3, 
	clr_Dark_Blue = 4,  
	clr_Dark_Magenta = 5,  
	clr_Dark_Cyan  = 6,  
	clr_Light_Gray = 7, 
	clr_Dark_Gray = 8, 
	clr_Red = 9, 
	clr_Green = 10, 
	clr_Yellow = 11, 
	clr_Blue = 12, 
	clr_Magenta = 13, 
	clr_Cyan = 14, 
	clr_White = 15, 
	clr_Transparent = 16 
};

enum D110DisplayAttribute
{ 
	dspl_Smbl_Name = 0, /* Display symbol with waypoint name */ 
	dspl_Smbl_Only = 1, /* Display symbol by itself */ 
	dspl_Smbl_Comment = 2 /* Display symbol with comment */ 
}; 

typedef struct 
{ 
	char name[17]; /* category name */ 
} D120_Wpt_Cat_Type;

typedef struct 
{ 
	char ident[6]; /* identifier */ 
	char cc[2]; /* country code */ 
	UInt8 wpt_class; /* class */ 
	position_type posn; /* position */ 
	SInt16 alt; /* altitude (meters) */ 
	char city[24]; /* city */ 
	char state[2]; /* state */ 
	char name[30]; /* facility name */ 
	char cmnt[40]; /* comment */ 
} D150_Wpt_Type; 

enum D150WaypointClass
{ 
	apt_wpt_class = 0, /* airport waypoint class */ 
	int_wpt_class = 1, /* intersection waypoint class */ 
	ndb_wpt_class = 2, /* NDB waypoint class */ 
	vor_wpt_class = 3, /* VOR waypoint class */ 
	usr_wpt_class = 4, /* user defined waypoint class */ 
	rwy_wpt_class = 5, /* airport runway threshold waypoint class */ 
	aint_wpt_class = 6, /* airport intersection waypoint class */ 
	locked_wpt_class = 7 /* locked waypoint class */
}; 

typedef struct 
{ 
	char ident[6]; /* identifier */ 
	position_type posn; /* position */ 
	UInt32 unused; /* should be set to zero */ 
	char cmnt[40]; /* comment */ 
	Float32 dst; /* proximity distance (meters) */ 
	char name[30]; /* facility name */ 
	char city[24]; /* city */ 
	char state[2]; /* state */ 
	SInt16 alt; /* altitude (meters) */ 
	char cc[2]; /* country code */ 
	char unused2; /* should be set to zero */ 
	UInt8 wpt_class; /* class */ 
} D151_Wpt_Type; 

enum D151WaypointClass
{ 
	apt_wpt_class = 0, /* airport waypoint class */ 
	vor_wpt_class = 1, /* VOR waypoint class */ 
	usr_wpt_class = 2, /* user defined waypoint class */ 
	locked_wpt_class = 3 /* locked waypoint class */ 
}; 

typedef struct 
{ 
	char ident[6]; /* identifier */ 
	position_type posn; /* position */ 
	UInt32 unused; /* should be set to zero */ 
	char cmnt[40]; /* comment */ 
	Float32 dst; /* proximity distance (meters) */ 
	char name[30]; /* facility name */ 
	char city[24]; /* city */ 
	char state[2]; /* state */ 
	SInt16 alt; /* altitude (meters) */ 
	char cc[2]; /* country code */ 
	UInt8 unused2; /* should be set to zero */ 
	UInt8 wpt_class; /* class */ 
} D152_Wpt_Type; 

enum D152WaypointClass
{ 
	apt_wpt_class = 0, /* airport waypoint class */ 
	int_wpt_class = 1, /* intersection waypoint class */ 
	ndb_wpt_class = 2, /* NDB waypoint class */ 
	vor_wpt_class = 3, /* VOR waypoint class */ 
	usr_wpt_class = 4, /* user defined waypoint class */ 
	locked_wpt_class = 5 /* locked waypoint class */ 
}; 

typedef struct 
{ 
	char ident[6]; /* identifier */ 
	position_type posn; /* position */ 
	UInt32 unused; /* should be set to zero */ 
	char cmnt[40]; /* comment */ 
	Float32 dst; /* proximity distance (meters) */ 
	char name[30]; /* facility name */ 
	char city[24]; /* city */ 
	char state[2]; /* state */ 
	SInt16 alt; /* altitude (meters) */ 
	char cc[2]; /* country code */ 
	UInt8 unused2; /* should be set to zero */ 
	UInt8 wpt_class; /* class */ 
	symbol_type smbl; /* symbol id */ 
} D154_Wpt_Type; 

enum D154WaypointClass
{ 
	apt_wpt_class = 0, /* airport waypoint class */ 
	int_wpt_class = 1, /* intersection waypoint class */ 
	ndb_wpt_class = 2, /* NDB waypoint class */ 
	vor_wpt_class = 3, /* VOR waypoint class */ 
	usr_wpt_class = 4, /* user defined waypoint class */ 
	rwy_wpt_class = 5, /* airport runway threshold waypoint class */ 
	aint_wpt_class = 6, /* airport intersection waypoint class */ 
	andb_wpt_class = 7, /* airport NDB waypoint class */ 
	sym_wpt_class = 8, /* user defined symbol-only waypoint class */ 
	locked_wpt_class = 9 /* locked waypoint class */ 
}; 

typedef struct 
{ 
	char ident[6]; /* identifier */ 
	position_type posn; /* position */ 
	UInt32 unused; /* should be set to zero */ 
	char cmnt[40]; /* comment */ 
	Float32 dst; /* proximity distance (meters) */ 
	char name[30]; /* facility name */ 
	char city[24]; /* city */ 
	char state[2]; /* state */ 
	SInt16 alt; /* altitude (meters) */ 
	char cc[2]; /* country code */ 
	UInt8 unused2; /* should be set to zero */ 
	UInt8 wpt_class; /* class */ 
	symbol_type smbl; /* symbol id */ 
	UInt8 dspl; /* display option */ 
} D155_Wpt_Type; 

enum D155DisplayOption
{ 
	dspl_smbl_only = 1, /* Display symbol by itself */ 
	dspl_smbl_name = 3, /* Display symbol with waypoint name */ 
	dspl_smbl_cmnt = 5, /* Display symbol with comment */ 
}; 

enum D155WaypointClass
{ 
	apt_wpt_class = 0, /* airport waypoint class */ 
	int_wpt_class = 1, /* intersection waypoint class */ 
	ndb_wpt_class = 2, /* NDB waypoint class */ 
	vor_wpt_class = 3, /* VOR waypoint class */ 
	usr_wpt_class = 4, /* user defined waypoint class */ 
	locked_wpt_class = 5 /* locked waypoint class */ 
}; 

typedef UInt8 D200_Rte_Hdr_Type; /* route number */

typedef struct 
{ 
	UInt8 nmbr; /* route number */ 
	char cmnt[20]; /* comment */ 
} D201_Rte_Hdr_Type; 

// Variable Length String
/*
typedef struct
{ 
	char rte_ident[];
} D202_Rte_Hdr_Type;
*/

typedef struct 
{ 
	UInt16 class; /* link class; see below */ 
	UInt8 subclass[18]; /* subclass */ 
	char ident[];   /* variable length string */ 
} D210_Rte_Link_Type; 

enum D210RouteClass
{ 
	line = 0, 
	link = 1, 
	net = 2, 
	direct = 3, 
	snap = 0xFF 
}; 

typedef struct 
{ 
	position_type posn; /* position */ 
	time_type time; /* time */ 
	bool new_trk; /* new track segment? */ 
} D300_Trk_Point_Type; 

typedef struct 
{ 
	position_type posn; /* position */ 
	time_type time; /* time */ 
	Float32 alt; /* altitude in meters */ 
	Float32 dpth; /* depth in meters */ 
	bool new_trk; /* new track segment? */ 
} D301_Trk_Point_Type; 

typedef struct 
{ 
	position_type posn; /* position */ 
	time_type time; /* time */ 
	Float32 alt; /* altitude in meters */ 
	Float32 dpth; /* depth in meters */ 
	Float32 temp; /* temp in degrees C */ 
	bool  new_trk; /* new track segment? */ 
} D302_Trk_Point_Type; 

typedef struct 
{ 
	position_type posn; /* position */ 
	time_type time; /* time */ 
	Float32 alt; /* altitude in meters */ 
	UInt8 heart_rate; /* heart rate in beats per minute */ 
} D303_Trk_Point_Type; 

typedef struct 
{ 
	position_type posn; /* position */ 
	time_type time; /* time */ 
	Float32 alt; /* altitude in meters */ 
	Float32 distance; /* distance traveled in meters. See below. */ 
	UInt8 heart_rate; /* heart rate in beats per minute */ 
	UInt8 cadence; /* in revolutions per minute */ 
	bool sensor; /* is a wheel sensor present? */ 
} D304_Trk_Point_Type; 

typedef struct 
{ 
	bool dspl; /* display on the map? */ 
	UInt8 color; /* color (same as D108) */ 
	char trk_ident[];   /* null-terminated string */ 
} D310_Trk_Hdr_Type; 

typedef struct 
{ 
	uint16 index; /* unique among all tracks received from device */ 
} D311_Trk_Hdr_Type; 

typedef struct 
{ 
	bool dspl; /* display on the map? */ 
	UInt8 color; /* color (see below) */ 
	char trk_ident[];   /* null-terminated string */ 
} D312_Trk_Hdr_Type; 

enum D312Color
{ 
	clr_Black = 0,  
	clr_Dark_Red = 1, 
	clr_Dark_Green = 2, 
	clr_Dark_Yellow = 3, 
	clr_Dark_Blue = 4,  
	clr_Dark_Magenta = 5,  
	clr_Dark_Cyan  = 6,  
	clr_Light_Gray = 7, 
	clr_Dark_Gray = 8, 
	clr_Red = 9, 
	clr_Green = 10, 
	clr_Yellow = 11, 
	clr_Blue = 12, 
	clr_Magenta = 13, 
	clr_Cyan = 14, 
	clr_White = 15, 
	clr_Transparent = 16, 
	clr_DefaultColor = 255 
}; 

typedef struct 
{ 
	D100_Wpt_Type wpt; /* waypoint */ 
	Float32 dst; /* proximity distance (meters) */ 
} D400_Prx_Wpt_Type; 

typedef struct 
{ 
	D103_Wpt_Type wpt; /* waypoint */ 
	Float32 dst; /* proximity distance (meters) */ 
} D403_Prx_Wpt_Type; 

typedef struct 
{ 
	// FIXME: In spec, idx is listed as an int. Going to assume they really mean that -- using SInt32
	SInt32 idx; /* proximity index */ 
	D150_Wpt_Type wpt; /* waypoint */ 
	Float32 dst; /* proximity distance (meters) */ 
} D450_Prx_Wpt_Type; 

typedef struct 
{ 
	UInt16 wn; /* week number (weeks) */ 
	Float32 toa; /* almanac data reference time (s) */ 
	Float32 af0; /* clock correction coefficient (s) */ 
	Float32 af1; /* clock correction coefficient (s/s) */ 
	Float32 e; /* eccentricity (-) */ 
	Float32 sqrta; /* square root of semi-major axis (a)(m**1/2) */ 
	Float32 m0; /* mean anomaly at reference time (r) */ 
	Float32 w; /* argument of perigee (r) */ 
	Float32 omg0; /* right ascension (r) */ 
	Float32 odot; /* rate of right ascension (r/s) */ 
	Float32 i; /* inclination angle (r) */ 
} D500_Almanac_Type; 

typedef struct 
{ 
	UInt16 wn; /* week number (weeks) */ 
	Float32 toa; /* almanac data reference time (s) */ 
	Float32 af0; /* clock correction coefficient (s) */ 
	Float32 af1; /* clock correction coefficient (s/s) */ 
	Float32 e; /* eccentricity (-) */ 
	Float32 sqrta; /* square root of semi-major axis (a)(m**1/2) */ 
	Float32 m0; /* mean anomaly at reference time (r) */ 
	Float32 w; /* argument of perigee (r) */ 
	Float32 omg0; /* right ascension (r) */ 
	Float32 odot; /* rate of right ascension (r/s) */ 
	Float32 i; /* inclination angle (r) */ 
	UInt8 hlth; /* almanac health */ 
} D501_Almanac_Type; 

typedef struct 
{ 
	UInt8 svid; /* satellite id */ 
	UInt16 wn; /* week number (weeks) */ 
	Float32 toa; /* almanac data reference time (s) */ 
	Float32 af0; /* clock correction coefficient (s) */ 
	Float32 af1; /* clock correction coefficient (s/s) */ 
	Float32 e; /* eccentricity (-) */ 
	Float32 sqrta; /* square root of semi-major axis (a)(m**1/2) */ 
	Float32 m0; /* mean anomaly at reference time (r) */ 
	Float32 w; /* argument of perigee (r) */ 
	Float32 omg0; /* right ascension (r) */ 
	Float32 odot; /* rate of right ascension (r/s) */ 
	Float32 i; /* inclination angle (r) */
} D550_Almanac_Type;

typedef struct 
{ 
	UInt8 svid; /* satellite id */ 
	UInt16 wn; /* week number (weeks) */ 
	Float32 toa; /* almanac data reference time (s) */ 
	Float32 af0; /* clock correction coefficient (s) */ 
	Float32 af1; /* clock correction coefficient (s/s) */ 
	Float32 e; /* eccentricity (-) */ 
	Float32 sqrta; /* square root of semi-major axis (a)(m**1/2) */ 
	Float32 m0; /* mean anomaly at reference time (r) */ 
	Float32 w; /* argument of perigee (r) */ 
	Float32 omg0; /* right ascension (r) */ 
	Float32 odot; /* rate of right ascension (r/s) */ 
	Float32 i; /* inclination angle (r) */ 
	UInt8 hlth; /* almanac health bits 17:24 (coded) */ 
} D551_Almanac_Type;  

typedef struct 
{ 
	UInt8 month; /* month  (1-12) */ 
	UInt8 day; /* day    (1-31) */ 
	UInt16 year; /* year   (1990 means 1990) */ 
	UInt16 hour; /* hour   (0-23) */ 
	UInt8 minute; /* minute (0-59) */ 
	UInt8 second; /* second (0-59) */ 
} D600_Date_Time_Type; 

typedef struct 
{ 
	time_type takeoff_time; /* Time flight started */ 
	time_type landing_time; /* Time flight ended */ 
	position_type  takeoff_posn; /* Takeoff lat/lon */ 
	position_type  landing_posn; /* Takeoff lat/lon */ 
	UInt32 night_time; /* Seconds flown in night time conditions */ 
	UInt32 num_landings; /* Number of landings during the flight */ 
	Float32 max_speed; /* Max velocity during flight (meters/sec) */ 
	Float32 max_alt; /* Max altitude above WGS84 ellipsoid (meters)*/ 
	Float32 distance; /* Distance of flight (meters) */ 
	bool cross_country_flag; /* Flight met cross country criteria */ 
	
	char strings[];
	/*
	char departure_name[];	// Name of airport      <= 31 bytes
	char departure_ident[]; // ID of airport        <= 11 bytes
	char arrival_name[];	// Name of airport      <= 31 bytes
	char arrival_ident[];	// ID of airport        <= 11 bytes
	char ac_id[];			// N Number of airplane <= 11 bytes
	*/
} D650_Flight_Book_Record_Type; 

typedef radian_position_type D700_Position_Type; 

typedef struct 
{ 
	Float32 alt; /* altitude above WGS 84 ellipsoid (meters) */ 
	Float32 epe; /* estimated position error, 2 sigma (meters) */ 
	Float32 eph; /* epe, but horizontal only (meters) */ 
	Float32 epv; /* epe, but vertical only (meters) */ 
	UInt16 fix; /* type of position fix */ 
	Float64 tow; /* time of week (seconds) */ 
	radian_position_type posn; /* latitude and longitude (radians) */ 
	Float32 east; /* velocity east  (meters/second) */ 
	Float32 north; /* velocity north (meters/second) */ 
	Float32 up; /* velocity up    (meters/second) */ 
	Float32 msl_hght; /* height of WGS84 ellipsoid above MSL(meters)*/ 
	SInt16 leap_scnds; /* difference between GPS and UTC (seconds) */ 
	UInt32 wn_days; /* week number days */ 
} D800_Pvt_Data_Type; 

enum D800FixType
{ 
	unusable = 0, /* failed integrity check */ 
	invalid = 1, /* invalid or unavailable */ 
	TwoD = 2, /* two dimensional */ 
	ThreeD = 3, /* three dimensional */ 
	TwoDee_diff = 4, /* two dimensional differential */ 
	ThreeD_diff = 5 /* three dimensional differential */ 
}; 

enum D800OldFixType
{ 
	unusable = 1, /* failed integrity check */ 
	invalid = 2, /* invalid or unavailable */ 
	TwoD = 3, /* two dimensional */ 
	ThreeD = 4, /* three dimensional */ 
	TwoD_diff = 5, /* two dimensional differential */ 
	ThreeD_diff = 6 /* three dimensional differential */
}; 

// TODO: Add table of devices/versions using old fix data

typedef struct 
{ 
	time_type start_time; 
	UInt32 total_time; /* In hundredths of a second */ 
	Float32  total_distance; /* In meters */ 
	position_type  begin; /* Invalid if both lat and lon are 0x7FFFFFFF */ 
	position_type end; /* Invalid if both lat and lon are 0x7FFFFFFF */ 
	UInt16 calories; 
	UInt8 track_index; /* See below */ 
	UInt8 unused; /* Unused. Set to 0. */ 
} D906_Lap_Type; 

// Note:
// D1002 out of order since it's used by D1000
typedef struct 
{ 
	UInt32 num_valid_steps; /* Number of valid steps (1-20) */ 
	struct 
	{ 
		char custom_name[16]; /* Null-terminated step name */ 
		Float32 target_custom_zone_low;  /* See below */ 
		Float32 target_custom_zone_high; /* See below */ 
		UInt16 duration_value; /* See below */ 
		UInt8 intensity;  /* Same as D1001 */ 
		UInt8 duration_type; /* See below */ 
		UInt8 target_type;  /* See below */ 
		UInt8 target_value;  /* See below */ 
		UInt16 unused;  /* Unused. Set to 0. */ 
	} steps[20]; 
	char name[16];  /* Null-terminated workout name */ 
	UInt8 sport_type;  /* Same as D1000 */ 
} D1002_Workout_Type; 

typedef struct 
{ 
	UInt32 track_index;  /* Index of associated track */ 
	UInt32 first_lap_index; /* Index of first associated lap */ 
	UInt32 last_lap_index; /* Index of last associated lap */ 
	UInt8 sport_type;  /* See below */ 
	UInt8 program_type;  /* See below */ 
	UInt16 unused;  /* Unused. Set to 0. */ 
	struct 
	{ 
		UInt32 time;  /* Time result of virtual partner */ 
		Float32 distance;  /* Distance result of virtual partner */ 
	} virtual_partner; 
	D1002_Workout_Type workout;  /* Workout */ 
} D1000_Run_Type;

enum D1000SportType
{ 
	running = 0, 
	biking = 1, 
	other = 2 
}; 

enum D1000ProgramType
{ 
	none = 0, 
	virtual_partner = 1, /* Completed with Virtual Partner */ 
	workout = 2 /* Completed as part of a workout */ 
}; 

typedef struct 
{ 
	UInt32 index; /* Unique among all laps received from device */ 
	time_type start_time; /* Start of lap time */ 
	UInt32 total_time; /* Duration of lap, in hundredths of a second */ 
	Float32 total_dist; /* Distance in meters */ 
	Float32 max_speed; /* In meters per second */ 
	position_type begin; /* Invalid if both lat and lon are 0x7FFFFFFF */ 
	position_type end; /* Invalid if both lat and lon are 0x7FFFFFFF */ 
	UInt16 calories; /* Calories burned this lap */ 
	UInt8 avg_heart_rate; /* In beats-per-minute, 0 if invalid */ 
	UInt8 max_heart_rate; /* In beats-per-minute, 0 if invalid */ 
	UInt8 intensity; /* See below */ 
} D1001_Lap_Type; 

enum D1001Intensity
{ 
	active = 0, /* This is a standard, active lap */ 
	rest
}; 

typedef struct 
{ 
	char workout_name[16]; /* Null-terminated workout name */ 
	time_type day;  /* Day on which the workout falls */ 
} D1003_Workout_Occurrence_Type; 

typedef struct 
{ 
	struct 
	{ 
		struct 
		{ 
			UInt8 low_heart_rate; /* In beats-per-minute, must be > 0 */ 
			UInt8 high_heart_rate; /* In beats-per-minute, must be > 0 */ 
			UInt16 unused;  /* Unused. Set to 0. */ 
		} heart_rate_zones[5]; 
		
		struct 
		{ 
			Float32 low_speed;  /* In meters-per-second */ 
			Float32 high_speed;  /* In meters-per-second */ 
			char name[16];  /* Null-terminated speed-zone name */ 
		} speed_zones[10]; 
	
		Float32 gear_weight;  /* Weight of equipment in kilograms */ 
		UInt8 max_heart_rate; /* In beats-per-minute, must be > 0 */ 
		UInt8 unused1;  /* Unused. Set to 0. */ 
		UInt16 unused2;  /* Unused. Set to 0. */ 
	} activities[3]; 
	
	Float32 weight;  /* User’s weight, in kilograms */ 
	UInt16 birth_year;  /* No base value (i.e. 1990 means 1990) */ 
	UInt8 birth_month;  /* 1 = January, etc. */ 
	UInt8 birth_day;  /* 1 = first day of month, etc. */ 
	UInt8 gender;  /* See below */ 
} D1004_Fitness_User_Profile_Type; 

enum D1004Gender 
{ 
	female = 0, 
	male = 1
}; 

typedef struct 
{ 
	UInt32 max_workouts;   /* Maximum workouts */ 
	UInt32 max_unscheduled_workouts; /* Maximum unscheduled workouts */ 
	UInt32 max_occurrences;  /* Maximum workout occurrences */ 
} D1005_Workout_Limits; 

typedef struct 
{ 
	UInt16 index;  /* Unique among courses on device */ 
	UInt16 unused;  /* Unused. Set to 0. */ 
	char course_name[16]; /* Null-terminated, unique course name */ 
	UInt16 track_index;  /* Index of the associated track */ 
} D1006_Course_Type; 

typedef struct 
{ 
	UInt16 course_index; /* Index of associated course */ 
	UInt16 lap_index; /* This lap’s index in the course */ 
	UInt32 total_time; /* In hundredths of a second */ 
	Float32 total_dist; /* In meters */ 
	position_type begin; /* Starting position of the lap */ 
	position_type end; /* Final position of the lap */ 
	UInt8 avg_heart_rate; /* In beats-per-minute */ 
	UInt8 max_heart_rate; /* In beats-per-minute */ 
	UInt8 intensity; /* Same as D1001 */ 
	UInt8 avg_cadence; /* In revolutions-per-minute */ 
} D1007_Course_Lap_Type; 

typedef struct 
{ 
	UInt32 num_valid_steps; /* Number of valid steps (1-20) */ 
	struct 
	{ 
		char custom_name[16]; /* Null-terminated step name */ 
		Float32 target_custom_zone_low;  /* See below */ 
		Float32 target_custom_zone_high; /* See below */ 
		UInt16 duration_value; /* Same as D1002 */ 
		UInt8 intensity;  /* Same as D1001 */ 
		UInt8 duration_type; /* Same as D1002 */ 
		UInt8 target_type;  /* See below */ 
		UInt8 target_value;  /* See below */ 
		UInt16 unused;  /* Unused. Set to 0. */ 
	} steps[20];
	
	char name[16];  /* Null-terminated workout name */ 
	UInt8 sport_type;  /* Same as D1000 */ 
} D1008_Workout_Type; 

typedef struct 
{ 
	UInt16 track_index;  /* Index of associated track */ 
	UInt16 first_lap_index; /* Index of first associated lap */ 
	UInt16 last_lap_index; /* Index of last associated lap */ 
	UInt8 sport_type;  /* Same as D1000 */ 
	UInt8 program_type;  /* See below */ 
	UInt8 multisport;  /* See below */ 
	UInt8 unused1;  /* Unused. Set to 0. */ 
	UInt16 unused2;  /* Unused. Set to 0. */ 
	struct 
	{ 
		UInt32 time;  /* Time result of quick workout */ 
		Float32 distance;  /* Distance result of quick workout */ 
	} quick_workout; 
	
	D1008_Workout_Type workout;  /* Workout */ 
} D1009_Run_Type; 

enum D1009Multisport
{ 
	no = 0, /* Not a MultiSport run */ 
	yes = 1, /* Part of a MultiSport session */ 
	yesAndLastInGroup = 2 /* The last of a MultiSport session */ 
}; 

typedef struct 
{ 
	UInt32 track_index;  /* Index of associated track */ 
	UInt32 first_lap_index; /* Index of first associated lap */ 
	UInt32 last_lap_index; /* Index of last associated lap */ 
	UInt8 sport_type;  /* Sport type (same as D1000) */ 
	UInt8 program_type;  /* See below */ 
	UInt8 multisport;  /* Same as D1009 */ 
	UInt8 unused;  /* Unused. Set to 0. */ 
	struct 
	{ 
		UInt32 time;  /* Time result of virtual partner */ 
		Float32 distance;  /* Distance result of virtual partner */ 
	} virtual_partner; 
	D1002_Workout_Type workout;  /* Workout */ 
} D1010_Run_Type; 

namespace foo
{
	int bar;
};

enum D1010ProgramType
{ 
	none = 0, 
	virtual_partner = 1, /* Completed with Virtual Partner */ 
	workout = 2, /* Completed as part of a workout */ 
	auto_multisport = 3 /* Completed as part of an auto MultiSport */ 
}; 	

typedef struct 
{ 
	UInt16 index; /* Unique among all laps received from device */ 
	UInt16 unused; /* Unused. Set to 0. */ 
	time_type start_time; /* Start of lap time */ 
	UInt32 total_time; /* Duration of lap, in hundredths of a second */ 
	Float32 total_dist; /* Distance in meters */ 
	Float32 max_speed; /* In meters per second */ 
	position_type begin; /* Invalid if both lat and lon are 0x7FFFFFFF */ 
	position_type end; /* Invalid if both lat and lon are 0x7FFFFFFF */ 
	UInt16 calories; /* Calories burned this lap */ 
	UInt8 avg_heart_rate; /* In beats-per-minute, 0 if invalid */ 
	UInt8 max_heart_rate; /* In beats-per-minute, 0 if invalid */ 
	UInt8 intensity; /* Same as D1001 */ 
	UInt8 avg_cadence; /* In revolutions-per-minute, 0xFF if invalid */ 
	UInt8 trigger_method; /* See below */ 
} D1011_Lap_Type; 

enum D1011TriggerMethod
{ 
	manual = 0, 
	distance = 1, 
	location = 2, 
	time = 3, 
	heart_rate = 4 
}; 

typedef struct 
{ 
	char name[11];  /* Null-terminated name */ 
	UInt8 unused1;  /* Unused. Set to 0. */ 
	UInt16 course_index;  /* Index of associated course */ 
	UInt16 unused2;  /* Unused. Set to 0. */ 
	time_type track_point_time; /* Time */ 
	UInt8 point_type;  /* See below */ 
} D1012_Course_Point_Type; 

enum D1012PointType
{ 
	generic = 0, 
	summit = 1, 
	valley = 2, 
	water = 3, 
	food = 4, 
	danger = 5, 
	left = 6, 
	right = 7, 
	straight = 8, 
	first_aid = 9, 
	fourth_category = 10, 
	third_category = 11, 
	second_category = 12, 
	first_category = 13, 
	hors_category = 14, 
	sprint = 15 
}; 

typedef struct 
{ 
	UInt32 max_courses;  /* Maximum courses */ 
	UInt32 max_course_laps; /* Maximum course laps */ 
	UInt32 max_course_pnt; /* Maximum course points */ 
	UInt32 max_course_trk_pnt; /* Maximum course track points */ 
} D1013_Course_Limits_Type; 

#endif // __GDATASTRUCTURES_H__
