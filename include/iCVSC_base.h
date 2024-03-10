#ifndef __ICVS_C_BASE_H__
#define __ICVS_C_BASE_H__

#include "iCVSCTypes.h"

#ifdef WIN32
#	ifdef ICVSC2_EXPORTS
#		define IC_API __declspec(dllexport)
#	else
#		define IC_API// __declspec(dllimport)
#	endif
#else
#	define IC_API
#endif

#ifndef WINAPI
#	ifdef WIN32
#		define WINAPI __stdcall
#	else
#		define WINAPI
#	endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

/* Initialize/uninitialize the protocol stack */
IC_API int WINAPI IC_Initialize(void);
IC_API int WINAPI IC_Terminate(void);
/* Enable/disable character set conversion */
IC_API int WINAPI IC_EnableConvertCharacter(int nEnableFlag);
/* Enable/disable bulk fetching of resources */
IC_API int WINAPI IC_EnableBatchForkResource(int nEnableFlag);

/* Login/exit platform */
IC_API int WINAPI IC_Open(const char *pszAddress, const char *pszUsername, const char *pszPassword, const char *pszEpid, IC_HANDLE *hSession);
IC_API int WINAPI IC_OpenByGateway(const char *pszAddress, const char *pszUsername, const char *pszPassword, const char *pszEpid, IC_HANDLE *hSession);
IC_API int WINAPI IC_OpenByProxy(const char *pszAddress, const char *pszUsername, const char *pszPassword, const char *pszEpid, int nFixAddr, 
								 const char *pszProxyType, const char *pszProxyAddr, const char *pszProxyUsername, const char *pszProxyPassword, IC_HANDLE *hSession);
IC_API int WINAPI IC_Close(IC_HANDLE hSession);
/* Get type of platform for login*/
IC_API int WINAPI IC_GetPlatformType(IC_HANDLE hSession, int *nPlatformType);

/* Receive notification (this interface has been deprecated, call IC_RecvEventMessageEx£© */
IC_API int WINAPI IC_ReceiveNotify(IC_HANDLE hSession, IC_STR szID, IC_STR szSrcID, int *nIndex, int *nUTC);

/* Building a single device */
IC_API int WINAPI IC_ForkOnePU(IC_HANDLE hSession, const char *pszPUID, IC_HANDLE *hPU);
/* Build the resources under the device*/
IC_API int WINAPI IC_ForkPUResource(IC_HANDLE hPU, IC_HANDLE *hResourcesArray, int *nArrayCount);

/* Get device handle through the resource handle */
IC_API int WINAPI IC_GetPUHandle(IC_HANDLE hResource, IC_HANDLE *hPU);
/* Get resource handle through the device handle*/
IC_API int WINAPI IC_GetResourceHandle(IC_HANDLE hPU, const char *pszType, int nIndex, IC_HANDLE *hResource);

/* Acquisition equipment model */
IC_API int WINAPI IC_GetPUModelName(IC_HANDLE hResource, IC_STR szModelName);
/* Get device vendor ID */
IC_API int WINAPI IC_GetPUManufactureID(IC_HANDLE hResource, IC_STR szManufactureID);
/*Get device hardware version number*/
IC_API int WINAPI IC_GetPUHardwareVersion(IC_HANDLE hResource, IC_STR szHardwareVersion);
/* Get device firmware version number */
IC_API int WINAPI IC_GetPUSoftwareVersion(IC_HANDLE hResource, IC_STR szSoftwareVersion);
/* Get device ID */
IC_API int WINAPI IC_GetPUDeviceID(IC_HANDLE hResource, IC_STR szDeviceID);
/* Get device type */
IC_API int WINAPI IC_GetPUModelType(IC_HANDLE hResource, IC_STR szModelType);
/* Get resources whether online */
IC_API int WINAPI IC_GetPUOnlineFlag(IC_HANDLE hResource, int *nOnlineFlag);
/* Get resource PUID */
IC_API int WINAPI IC_GetResourcePUID(IC_HANDLE hResource, IC_STR szPUID);
/* Get resource type */
IC_API int WINAPI IC_GetResourceType(IC_HANDLE hResource, IC_STR szType);
/* Get resource index */
IC_API int WINAPI IC_GetResourceIndex(IC_HANDLE hResource, int *nIndex);
/* Get whether resource is available */
IC_API int WINAPI IC_GetResourceUsable(IC_HANDLE hResource, int *nUsable);

/* Get/set resource name */
IC_API int WINAPI IC_GetResourceName(IC_HANDLE hResource, IC_STR szName);
IC_API int WINAPI IC_SetResourceName(IC_HANDLE hResource, const char *pszName);

/* Get/set resource description */
IC_API int WINAPI IC_GetResourceDescription(IC_HANDLE hResource, IC_STR szDescription);
IC_API int WINAPI IC_SetResourceDescription(IC_HANDLE hResource, const char *pszDescription);

/* Get/set whether resource is enabled */
IC_API int WINAPI IC_GetResourceEnable(IC_HANDLE hResource, int *nEnable);
IC_API int WINAPI IC_SetResourceEnable(IC_HANDLE hResource, int nEnable);

/* Start video/audio stream*/
IC_API int WINAPI IC_StartStream(IC_HANDLE hResource, int nStreamID, IC_HANDLE *hStream);
/* Start communicating */
IC_API int WINAPI IC_StartCall(IC_HANDLE hResource, IC_HANDLE *hStream);
/* Start intercom flow*/
IC_API int WINAPI IC_StartTalk(IC_HANDLE hResource, IC_HANDLE *hStream);
/* Start snap flow*/
IC_API int WINAPI IC_StartSnapshotStream(IC_HANDLE hResource, int nInterval, IC_HANDLE *hStream);
/* Stop stream */
IC_API int WINAPI IC_StopStream(IC_HANDLE hStream);

/* Receive a frame of data */
IC_API int WINAPI IC_ReceiveFrame(IC_HANDLE hStream, char *pFrame, int *nLen, int *nFrameType, int *nKeyFrameFlag);
/* Receive one frame of PS frame data£¬ */
IC_API int WINAPI IC_ReceivePSFrame(IC_HANDLE hStream, char *pPSFrame, int *nPSLen);
/* Receive GPS frame data*/
IC_API int WINAPI IC_ReceiveGPSFrame(IC_HANDLE hStream, IC_GNSS_DATA *pGPSData);
/* Send a frame of data*/
IC_API int WINAPI IC_SendFrame(IC_HANDLE hStream, char *pFrame, int nLen, int nFrameType);
/*Send an end package*/
IC_API int WINAPI IC_SendEndPacket(IC_HANDLE hStream);

/* Device configuration*/
/* Vendor ID */
IC_API int WINAPI IC_GetProducerID(IC_HANDLE hResource, IC_STR szProducerID);
/* OEM data */
IC_API int WINAPI IC_GetOEMData(IC_HANDLE hResource, char *szOEMData, int *nLen);
IC_API int WINAPI IC_SetOEMData(IC_HANDLE hResource, const char *pszOEMData);
/* Device control */
/* Send the command to restart the video server */
IC_API int WINAPI IC_Reboot(IC_HANDLE hResource);

/* Get the time nTime in UTC format*/
IC_API int WINAPI IC_GetTime(IC_HANDLE hResource, int *nTime);
/* Set the time nTime to UTC format*/
IC_API int WINAPI IC_SetTime(IC_HANDLE hResource, int nTime);

/* Input video configuration */
/* Camera status */
IC_API int WINAPI IC_GetCameraStatus(IC_HANDLE hResource, int *nCameraStatus);
/* Brightness */
IC_API int WINAPI IC_GetBrightness(IC_HANDLE hResource, int *nBrightness);
IC_API int WINAPI IC_SetBrightness(IC_HANDLE hResource, int nBrightness);
IC_API int WINAPI IC_PreviewBrightness(IC_HANDLE hResource, int nBrightness);
/* Contrast*/
IC_API int WINAPI IC_GetContrast(IC_HANDLE hResource, int *nContrast);
IC_API int WINAPI IC_SetContrast(IC_HANDLE hResource, int nContrast);
IC_API int WINAPI IC_PreviewContrast(IC_HANDLE hResource, int nContrast);
/* Hue */
IC_API int WINAPI IC_GetHue(IC_HANDLE hResource, int *nHue);
IC_API int WINAPI IC_SetHue(IC_HANDLE hResource, int nHue);
IC_API int WINAPI IC_PreviewHue(IC_HANDLE hResource, int nHue);
/* Saturation */
IC_API int WINAPI IC_GetSaturation(IC_HANDLE hResource, int *nSaturation);
IC_API int WINAPI IC_SetSaturation(IC_HANDLE hResource, int nSaturation);
IC_API int WINAPI IC_PreviewSaturation(IC_HANDLE hResource, int nSaturation);
/* Coding resolution */
IC_API int WINAPI IC_GetResolution(IC_HANDLE hResource, int nStreamID, IC_STR szResolution);
IC_API int WINAPI IC_SetResolution(IC_HANDLE hResource, int nStreamID, const char *pszResolution);
/* Target bit rate */
IC_API int WINAPI IC_GetBitRate(IC_HANDLE hResource, int nStreamID, int *nBitRate);
IC_API int WINAPI IC_SetBitRate(IC_HANDLE hResource, int nStreamID, int nBitRate);
/* Target frame rate */
IC_API int WINAPI IC_GetFrameRate(IC_HANDLE hResource, int nStreamID, int *nFrameRate);
IC_API int WINAPI IC_SetFrameRate(IC_HANDLE hResource, int nStreamID, int nFrameRate);
/* Target definition*/
IC_API int WINAPI IC_GetImageDefinition(IC_HANDLE hResource, int nStreamID, int *nImageDefinition);
IC_API int WINAPI IC_SetImageDefinition(IC_HANDLE hResource, int nStreamID, int nImageDefinition);
/* Whether to stack time */
IC_API int WINAPI IC_GetAddTime(IC_HANDLE hResource, int nStreamID, int *nAddTime);
IC_API int WINAPI IC_SetAddTime(IC_HANDLE hResource, int nStreamID, int nAddTime);
/* Whether to stack text */
IC_API int WINAPI IC_GetAddText(IC_HANDLE hResource, int nStreamID, int *nAddText);
IC_API int WINAPI IC_SetAddText(IC_HANDLE hResource, int nStreamID, int nAddText);
/* Stack text content*/
IC_API int WINAPI IC_GetTextAdd(IC_HANDLE hResource, IC_STR szTextAdd);
IC_API int WINAPI IC_SetTextAdd(IC_HANDLE hResource, const char *pszTextAdd);
/* Input video control*/
/* Request to send frame I*/
IC_API int WINAPI IC_StartKeyFrame(IC_HANDLE hResource, int nStreamID);

/* Output audio configuration */
/* Decoding algorithm */
IC_API int WINAPI IC_GetAudioDecoder(IC_HANDLE hResource, IC_STR szDecoder);
IC_API int WINAPI IC_SetAudioDecoder(IC_HANDLE hResource, const char *pszDecoder);
/* Decoding algorithm vendor ID */
IC_API int WINAPI IC_GetDecoderProducerID(IC_HANDLE hResource, IC_STR szDecoderProducerID);

/* Serial port configuration */
/* Baud rate */
IC_API int WINAPI IC_GetBaudRate(IC_HANDLE hResource, int *nBaudRate);
IC_API int WINAPI IC_SetBaudRate(IC_HANDLE hResource, int nBaudRate);
/* Data bits */
IC_API int WINAPI IC_GetDataBits(IC_HANDLE hResource, int *nDataBits);
IC_API int WINAPI IC_SetDataBits(IC_HANDLE hResource, int nDataBits);
/* Check digit */
IC_API int WINAPI IC_GetParity(IC_HANDLE hResource, IC_STR szParity);
IC_API int WINAPI IC_SetParity(IC_HANDLE hResource, const char *pszParity);
/* Stop bit */
IC_API int WINAPI IC_GetStopBits(IC_HANDLE hResource, int *nStopBits);
IC_API int WINAPI IC_SetStopBits(IC_HANDLE hResource, int nStopBits);
/* Serial port control */
/* Sending data */
IC_API int WINAPI IC_WriteData(IC_HANDLE hResource, char *pData, int nLen);

/* PTZ configuration */
/* The speed of PTZ movement */
IC_API int WINAPI IC_GetSpeed(IC_HANDLE hResource, int *nSpeed);
IC_API int WINAPI IC_SetSpeed(IC_HANDLE hResource, int nSpeed);
/* PTZ control */
/* Turn left */
IC_API int WINAPI IC_StartTurnLeft(IC_HANDLE hResource, int nDegree);
/* Turn right */
IC_API int WINAPI IC_StartTurnRight(IC_HANDLE hResource, int nDegree);
/* Turn up*/
IC_API int WINAPI IC_StartTurnUp(IC_HANDLE hResource, int nDegree);
/* Turn down */
IC_API int WINAPI IC_StartTurnDown(IC_HANDLE hResource, int nDegree);
/* Stop running */
IC_API int WINAPI IC_StopTurn(IC_HANDLE hResource);
/* Increase aperture */
IC_API int WINAPI IC_AugmentAperture(IC_HANDLE hResource);
/* Reduce aperture */
IC_API int WINAPI IC_MinishAperture(IC_HANDLE hResource);
/* Stop aperture scaling */
IC_API int WINAPI IC_StopApertureZoom(IC_HANDLE hResource);
/* Push */
IC_API int WINAPI IC_MakeFocusFar(IC_HANDLE hResource);
/* Closer focus */
IC_API int WINAPI IC_MakeFocusNear(IC_HANDLE hResource);
/* Stop focus adjustment */
IC_API int WINAPI IC_StopFocusMove(IC_HANDLE hResource);
/* Shrink image*/
IC_API int WINAPI IC_ZoomOutPicture(IC_HANDLE hResource);
/* Enlarge image */
IC_API int WINAPI IC_ZoomInPicture(IC_HANDLE hResource);
/* Stop zooming */
IC_API int WINAPI IC_StopPictureZoom(IC_HANDLE hResource);
/* Go to preset */
IC_API int WINAPI IC_MoveToPresetPos(IC_HANDLE hResource, int nPresetPos);
/* Set preset */
IC_API int WINAPI IC_SetPresetPos(IC_HANDLE hResource, int nPresetPos, const char *pszName);

/* Output alarm configuration */
/* Alarm output current status */
IC_API int WINAPI IC_GetConnectStatus(IC_HANDLE hResource, int *nConnectStatus);
/* Control alarm output status */
IC_API int WINAPI IC_SetStatus(IC_HANDLE hResource, int nStatus);

/* Front end storage control */
/* Start video recording */
IC_API int WINAPI IC_StartRecord(IC_HANDLE hResource, int nIndex, int nDuration, const char *pszReason);
/* Stop video recording */
IC_API int WINAPI IC_StopRecord(IC_HANDLE hResource, int nIndex);
/* Start capture */
IC_API int WINAPI IC_StartSnapshot(IC_HANDLE hResource, int nIndex, int nNumber, int nInterval, const char *pszReason);
/* Query video/picture files */
IC_API int WINAPI IC_QueryFile(IC_HANDLE hResource, int nIndex, int nBegin, int nEnd, int nType, int nOffset, IC_FILE_INFO *rfiaFileInfos, int *nCount);
/* Download video/picture files */
IC_API int WINAPI IC_DownloadFile(IC_HANDLE hResource, const char *pszFile, int nOffset, int nLength, IC_HANDLE *hStream);
/* Demand video, At present, there's no return vod ID, which is not supported to control by ID  */
IC_API int WINAPI IC_VODFile(IC_HANDLE hResource, const char *pszFile, int nDirection, int nStartTime, IC_STR szVodID, IC_HANDLE *hStream);
/* Time-lapse video on demand, At present, there's no return vod ID, which is not supported to control by ID  */
IC_API int WINAPI IC_VODTime(IC_HANDLE hResource, int nIndex, int nBeginTime, int nEndTime, IC_STR szVodID, IC_HANDLE *hStream);
/* On demand to suspend,At present, there's no return vod ID, which is not supported to control by ID  */
IC_API int WINAPI IC_VODPause(IC_HANDLE hResource, const char *pszVodID);
/* Vod recovery,At present, there's no return vod ID, which is not supported to control by ID */
IC_API int WINAPI IC_VODResume(IC_HANDLE hResource, const char *pszVodID);
/* Change the playing position on demand, At present, there's no return vod ID, which is not supported to control by ID */
IC_API int WINAPI IC_VODChangePosition(IC_HANDLE hResource, const char *pszVodID, int nPosition);
///* Change the sending speed on demand */
//IC_API int WINAPI IC_VODChangeRate(IC_HANDLE hResource, const char *pszVodID, int nRate);
///* Query historical GPRS data */
//IC_API int WINAPI IC_QueryGPSData(IC_HANDLE hResource, int nBeginTime, int nEndTime, int nOffset, IC_GNSS_DATA *gdaGPSDatas, int *nCount);

/* Download and collect data by time */
IC_API int WINAPI IC_DownloadOPCByTime(IC_HANDLE hResource, int nIndex, int nType, int nBeginTime, int nEndTime, IC_STR szVodID, IC_HANDLE *hStream);
#ifdef __cplusplus
}
#endif

#endif /* __ICVS_C_BASE_H__ */
