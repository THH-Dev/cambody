#include <iostream>
#ifndef __ICVS_TYPES_H__
#define __ICVS_TYPES_H__

/* constant definition */
#define MAX_STR_LEN				256				/* Maximum string length */

/* Platform Type */
#define PLATFORM_TYPE_DEVICE	0				/* Device */
#define PLATFORM_TYPE_CMS		1				/* Platform */

/* Frame type */
#define FRAME_TYPE_VIDEO		1				/* Video frame */
#define FRAME_TYPE_AUDIO		2				/* Audio frame */
#define FRAME_TYPE_DATA			3				/* Data frame */
#define FRAME_TYPE_GPS			4				/* GPS frame */
#define FRAME_TYPE_SP			5				/* Serial port frame */
#define FRAME_TYPE_PIC			6				/* Picture frame */
#define FRAME_TYPE_MSG			7				/* Message frame */
#define FRAME_TYPE_WD			8				/* WIFI probe frame */
#define FRAME_TYPE_R_AUDIO		9				/* Reverse audio frame */

/* Event (notification) type*/
#define NOTIFY_TYPE_NORMAL		0				/* Ordinary events*/
#define NOTIFY_TYPE_INTELL		5				/* Intelligent analysis of events */
#define NOTIFY_TYPE_EXTENDAPP	6				/* Extended application events */
#define NOTIFY_TYPE_WIFIPROBER	7				/* WiFi probe events */


/* Resource type */
#define RESOURCE_TYPE_ST		"ST"			/* The site itself */
#define RESOURCE_TYPE_IV		"IV"			/* The input video(Input Video, IV) */
#define RESOURCE_TYPE_IA		"IA"			/* The input audio(Input Audio, IA) */
#define RESOURCE_TYPE_OV		"OV"			/* The output video(Output Video, OV) */
#define RESOURCE_TYPE_OA		"OA"			/* The output audio(Output Audio, OA) */
#define RESOURCE_TYPE_SP		"SP"			/* Serial port(Serial Port, SP) */
#define RESOURCE_TYPE_PTZ		"PTZ"			/* PTZ(PTZ) */
#define RESOURCE_TYPE_IDL		"IDL"			/* Input digital line(Input Digital Line, IDL) */
#define RESOURCE_TYPE_ODL		"ODL"			/* Output digital line(Output Digital Line, ODL) */
#define RESOURCE_TYPE_DP		"DP"			/* Display device(Displayer) */
#define RESOURCE_TYPE_SG		"SG"			/* Storager(Storager, SG) */
#define RESOURCE_TYPE_WIFI		"WIFI"			/* WIFI module */
#define RESOURCE_TYPE_WM		"WM"			/* Wireless dial module(Wireless Module) */
#define RESOURCE_TYPE_GPS		"GPS"			/* GPS */

/* Device Type */
#define DEVICE_TYPE_ENC			"ENC"			/* Wired encoder */
#define DEVICE_TYPE_WENC		"WENC"			/* Wireless encoder */
#define DEVICE_TYPE_DEC			"DEC"			/* Wired decoder */
#define DEVICE_TYPE_WDEC		"WDEC"			/* Wireless decoer */
#define DEVICE_TYPE_GPS			"GPS"			/* GPS device */
#define DEVICE_TYPE_ALARM		"ALARM"			/* Alarm host */

/* Type defintion */
typedef	void*			IC_HANDLE;				/* Handle */
typedef char			IC_STR[MAX_STR_LEN];	/* String type */

/* Time period*/
typedef struct _TIME_SET
{
	IC_STR szBegin;								/* Starting time */
	IC_STR szEnd;								/* End time */
	int nWeekday;								/* Week */
} TIME_SET;

/* File info */
typedef struct _FILE_INFO 
{
	char szPUID[64];							/* Device ID */
	int nResIdx;								/* Channel index */
	char szName[32];							/* File name */
	char szPath[256];							/*File path */
	char szReasons[256];						/* Video REC reason */
	char szID[64];								/* Storage ID */
	int nSize;									/* File size */
	union 
	{
		struct 
		{
			int nBeginTime;						/* Starting time */
			int nEndTime;						/* End time */
		} record;
		struct 
		{
			int nTime;							/* Snap time */
			int nNoInSecond;					/* No. in sencond */
		} snapshot;
	} un;
} IC_FILE_INFO;

/* Positioning data*/
typedef struct _GNSS_DATA
{
	unsigned int uiUTC;							/* UTC time£¬unit second */
	double dLongitude;							/* Longitude, unit degree */
	double dLatitude;							/* Latitude, unit degree */
	float fBearing;								/* Direction, unit degree */
	float fSpeed;								/* Speed, kilometers per hour */
	int nAltitude;								/* Altitude, unit meters */
	int nType;									/* Positioning system type: 0 means undefined, 1 means beidou, 2 means GPS, and 3 means mixed */
	int nUpperSpeed;							/* Maximum speed limit, unit km/h */
	int nLowestSpeed;							/* Minimum speed limit, unit km/h */
	float fMileage;								/* Statistics mileage, unit meters */


	void init()
	{
		uiUTC = 0;							/* UTC time£¬unit second */
		dLongitude = 0;							/* Longitude, unit degree */
		dLatitude = 0;							/* Latitude, unit degree */
		fBearing = 0;								/* Direction, unit degree */
		fSpeed = 0;								/* Speed, kilometers per hour */
		nAltitude = 0;								/* Altitude, unit meters */
		nType = 0;									/* Positioning system type: 0 means undefined, 1 means beidou, 2 means GPS, and 3 means mixed */
		nUpperSpeed = 0;							/* Maximum speed limit, unit km/h */
		nLowestSpeed = 0;							/* Minimum speed limit, unit km/h */
		fMileage = 0;								/* Statistics mileage, unit meters */
	}
	void print()
	{
	
		TRACE("dLatitude = %f\n", dLatitude);
		TRACE("fBearing = %f\n", fBearing);
		TRACE("fSpeed = %f\n", fSpeed);
		TRACE("nAltitude = %d\n", nAltitude);
		TRACE("nType = %d\n", nType);
		TRACE("nUpperSpeed = %d\n", nUpperSpeed);
		TRACE("nLowestSpeed = %d\n", nLowestSpeed);
		TRACE("fMileage = %f\n", fMileage);
	}
} IC_GNSS_DATA;

#endif /* __ICVS_TYPES_H__ */
