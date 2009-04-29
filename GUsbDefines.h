#ifndef __GUSBDEFINES_H__
#define __GUSBDEFINES_H__

/*
 *  GUsbDefines.h
 *  GarminKit
 *
 *  Created by Jon Nall on 11/2/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "GDefines.h"

#define API_VERSION 1 
#define MAX_BUFFER_SIZE 4096
#define ASYNC_DATA_SIZE 64 

enum Link000PacketID
{ 
	Pid_Data_Available = 2, 
	Pid_Start_Session = 5, 
	Pid_Session_Started = 6,

	Pid_Protocol_Array = 253, /* may not be implemented in all devices */ 
	Pid_Product_Rqst = 254, 
	Pid_Product_Data = 255, 
	Pid_Ext_Product_Data = 248 /* may not be implemented in all devices */ 
}; 

enum Link001PacketID
{ 
	Pid_Command_Data  =  10, 
	Pid_Xfer_Cmplt  =  12, 
	Pid_Date_Time_Data  =  14, 
	Pid_Position_Data  =  17, 
	Pid_Prx_Wpt_Data  =  19, 
	Pid_Records  =  27, 
	Pid_Rte_Hdr  =  29, 
	Pid_Rte_Wpt_Data  =  30, 
	Pid_Almanac_Data  =  31, 
	Pid_Trk_Data  =  34, 
	Pid_Wpt_Data  =  35, 
	Pid_Pvt_Data  =  51, 
	Pid_Rte_Link_Data  =  98, 
	Pid_Trk_Hdr  =  99, 
	Pid_FlightBook_Record  = 134, 
	Pid_Lap  = 149, 
	Pid_Wpt_Cat  = 152, 
	Pid_Run  = 990, 
	Pid_Workout  = 991, 
	Pid_Workout_Occurrence  = 992, 
	Pid_Fitness_User_Profile = 993, 
	Pid_Workout_Limits  = 994, 
	Pid_Course  = 1061, 
	Pid_Course_Lap  = 1062, 
	Pid_Course_Point  = 1063, 
	Pid_Course_Trk_Hdr  = 1064, 
	Pid_Course_Trk_Data  = 1065, 
	Pid_Course_Limits  = 1066 
}; 

enum Link002PacketID
{ 
	Pid_Almanac_Data =  4, 
	Pid_Command_Data = 11, 
	Pid_Xfer_Cmplt = 12, 
	Pid_Date_Time_Data = 20, 
	Pid_Position_Data = 24, 
	Pid_Prx_Wpt_Data = 27, 
	Pid_Records = 35, 
	Pid_Rte_Hdr = 37, 
	Pid_Rte_Wpt_Data = 39, 
	Pid_Wpt_Data = 43
}; 

enum ProtocolTagValue
{ 
	Tag_Phys_Prot_Id = 'P', /* ‘P’ tag for Physical protocol ID */ 
	Tag_Link_Prot_Id = 'L', /* 'L' tag for Link protocol ID */ 
	Tag_Appl_Prot_Id = 'A', /* 'A' tag for Application protocol ID */ 
	Tag_Data_Type_Id = 'D' /* 'D' tag for Data Type ID */ 
}; 

enum App010PacketID
{ 
	Cmnd_Abort_Transfer  =  0, /* abort current transfer */ 
	Cmnd_Transfer_Alm  =  1, /* transfer almanac */ 
	Cmnd_Transfer_Posn  =  2, /* transfer position */ 
	Cmnd_Transfer_Prx  =  3, /* transfer proximity waypoints */ 
	Cmnd_Transfer_Rte  =  4, /* transfer routes */ 
	Cmnd_Transfer_Time  =  5, /* transfer time */ 
	Cmnd_Transfer_Trk  =  6, /* transfer track log */ 
	Cmnd_Transfer_Wpt  =  7, /* transfer waypoints */ 
	Cmnd_Turn_Off_Pwr  =  8, /* turn off power */ 
	Cmnd_Start_Pvt_Data  = 49, /* start transmitting PVT data */ 
	Cmnd_Stop_Pvt_Data  = 50, /* stop transmitting PVT data */ 
	Cmnd_FlightBook_Transfer = 92, /* transfer flight records */ 
	Cmnd_Transfer_Laps  = 117, /* transfer fitness laps */ 
	Cmnd_Transfer_Wpt_Cats  = 121, /* transfer waypoint categories */ 
	Cmnd_Transfer_Runs  = 450, /* transfer fitness runs */ 
	Cmnd_Transfer_Workouts  = 451, /* transfer workouts */ 
	Cmnd_Transfer_Workout_Occurrences = 452, /* transfer workout occurrences */ 
	Cmnd_Transfer_Fitness_User_Profile = 453, /* transfer fitness user profile */ 
	Cmnd_Transfer_Workout_Limits = 454, /* transfer workout limits */ 
	Cmnd_Transfer_Courses  = 561, /* transfer fitness courses */ 
	Cmnd_Transfer_Course_Laps = 562, /* transfer fitness course laps */ 
	Cmnd_Transfer_Course_Points = 563, /* transfer fitness course points */ 
	Cmnd_Transfer_Course_Tracks = 564, /* transfer fitness course tracks */ 
	Cmnd_Transfer_Course_Limits = 565 /* transfer fitness course limits */ 
}; 

enum App011PacketID
{ 
	Cmnd_Abort_Transfer =  0, /* abort current transfer */ 
	Cmnd_Transfer_Alm =  4, /* transfer almanac */ 
	Cmnd_Transfer_Rte =  8, /* transfer routes */ 
	Cmnd_Transfer_Prx = 17, /* transfer proximity waypoints */ 
	Cmnd_Transfer_Time = 20, /* transfer time */ 
	Cmnd_Transfer_Wpt = 21, /* transfer waypoints */ 
	Cmnd_Turn_Off_Pwr = 26 /* turn off power */ 
}; 

#endif // __GUSBDEFINES_H__


