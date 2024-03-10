#ifndef __ICVS_C_H__
#define __ICVS_C_H__

#include "iCVSC_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Get connection ID */
IC_API int WINAPI IC_GetSessionID(IC_HANDLE hSession, IC_STR szSessionID);
/* Get user priority */
IC_API int WINAPI IC_GetPriority(IC_HANDLE hSession, int *nPriority);

/* Process platform command */
IC_API int WINAPI IC_TransCusMessage(IC_HANDLE hSession, const char *pszRequest, char **szResponse);
/* Process device command */
IC_API int WINAPI IC_TransComMessage(IC_HANDLE hSession, const char *pszPUID, const char *pszRequest, char **szResponse);
/* Process other commands */
IC_API int WINAPI IC_TransMessage(IC_HANDLE hSession, int nType, const char *pszID, const char *pszRequest, char **szResponse);
/* Handles device commands in a non-blocking manner */
IC_API int WINAPI IC_SendComReq(IC_HANDLE hSession, const char *pszPUID, const char *pszRequest, int *nTransID);
IC_API int WINAPI IC_SendComReqWithDomainRoad(IC_HANDLE hSession, int nType, const char *pszDomainRoad, const char *pszRequest, int *nTransID);
IC_API int WINAPI IC_RecvComRsp(IC_HANDLE hSession, int nTransID, char **szResponse);
IC_API int WINAPI IC_CancelReq(IC_HANDLE hSession, int nTransID);

/* Receive events (this interface has been deprecated, call IC_RecvEventMessageEx)*/
IC_API int WINAPI IC_RecvEventMessage(IC_HANDLE hSession, char **szEventMessage);
/* Receive events*/
IC_API int WINAPI IC_RecvEventMessageEx(IC_HANDLE hSession, int *nType, char **szEventMessage);


/* Release command response buffer area */
IC_API int WINAPI IC_ReleaseMessage(IC_HANDLE hSession, char *szMessage);

/* Get platform name */
IC_API int WINAPI IC_GetSystemName(IC_HANDLE hSession, IC_STR szSystemName);
/* Get platform description*/
IC_API int WINAPI IC_GetSystemDescription(IC_HANDLE hSession, IC_STR szSystemDescription);

/* Get all the subdomains of the platform*/
IC_API int WINAPI IC_GetSubDomain(IC_HANDLE hSession, IC_STR *szaDomainRoad, IC_STR *szaDomainName, int *nCount);

/* Build the list of devices under the platform */
IC_API int WINAPI IC_ForkPUList(IC_HANDLE hSession, int nOffset, IC_HANDLE *hPUArray, int *nCount);
IC_API int WINAPI IC_ForkSubDomainPUList(IC_HANDLE hSession, const char *pszDomain, int nOffset, IC_HANDLE *hPUArray, int *nCount);

/* Get device installation longitude */
IC_API int WINAPI IC_GetPULongitude(IC_HANDLE hResource, double *dbLongitude);
/* Get device installation latitude*/
IC_API int WINAPI IC_GetPULatitude(IC_HANDLE hResource, double *dbLatitude);
/* Get device domain path */
IC_API int WINAPI IC_GetPUSubDomain(IC_HANDLE hResource, IC_STR szDomainRoad, IC_STR szDomainName);

/* Start transcoding streams flow of video/audio platform*/
IC_API int WINAPI IC_StartTranscodeStream(IC_HANDLE hSession, const char *szAlg, const char *szResolution, int nBitRate, int nFrameRate, IC_HANDLE *hStream);

/* Platform storage control */
/* Manually start storage */
IC_API int WINAPI IC_CSSManualStart(IC_HANDLE hSession, const char *pszReason, int nDuration, int nType, int nReserveDay, int nFileLength, const char *pszPUID, int nIndex, int nStreamID, int nAudioFlag, IC_STR szID);
/* Manually stop storage */
IC_API int WINAPI IC_CSSManualStop(IC_HANDLE hSession, const char *pszID);
/* Query video/picture files */
IC_API int WINAPI IC_CSSQueryFile(IC_HANDLE hSession, int nBeginTime, int nEndTime, int nType, const IC_STR *pReason, int nReasonCnt, const IC_HANDLE *pRes, int nResCnt, int nOffset, IC_FILE_INFO *rfiaFileInfos, int *nCount);
/* Query upload file*/
IC_API int WINAPI IC_CSSQueryUploadFile(IC_HANDLE hSession, int nBeginTime, int nEndTime, const char *pszLogicMode, const IC_STR *pReason, int nReasonCnt, int nOffset, IC_FILE_INFO *rfiaFileInfos, int *nCount);
/* Delete video/picture files */
IC_API int WINAPI IC_CSSDeleteFile(IC_HANDLE hSession, int nType, const IC_STR *szaFiles, const IC_STR *szaID, int nCount);
/* Download file (including pictures) */
IC_API int WINAPI IC_CSSDownloadFile(IC_HANDLE hSession, const char *pszID, const char *pszFile, int nOffset, int nLength, IC_HANDLE *hStream);
/* Demand file */
IC_API int WINAPI IC_CSSVODFile(IC_HANDLE hSession, const char *pszID, const char *pszFile, int nDirection, int nStartTime, int nDuration, int nRate, IC_STR szVodID, IC_HANDLE *hStream);
/* Demand period */
IC_API int WINAPI IC_CSSVODTime(IC_HANDLE hSession, IC_HANDLE hRes, int nBeginTime, int nEndTime, int nRate, IC_STR szVodID, IC_HANDLE *hStream);
/* Demand pause */
IC_API int WINAPI IC_CSSVODPause(IC_HANDLE hSession, const char *pszVodID);
/* Demand recover*/
IC_API int WINAPI IC_CSSVODResume(IC_HANDLE hSession, const char *pszVodID);
/* Change playing position on demand */
IC_API int WINAPI IC_CSSVODChangePosition(IC_HANDLE hSession, const char *pszVodID, int nPosition);
/* Change sending speed on demand */
IC_API int WINAPI IC_CSSVODChangeRate(IC_HANDLE hSession, const char *pszVodID, int nRate);
/* Upload file */
IC_API int WINAPI IC_CSSUploadFile(IC_HANDLE hSession, const char *pszFilename, int nTime, int nReserveDay, const IC_STR *szaReason, int nCount, IC_STR szID, int *nLength, IC_HANDLE *hStream);
/* Upload video recording */
IC_API int WINAPI IC_CSSUploadRecord(IC_HANDLE hSession, const char *pszPUID, int nIndex, int nStreamID, const char *pszReason, int nReserveDay, int nFileLength, IC_HANDLE *hStream);

#ifdef __cplusplus
}
#endif
 
#endif /* __ICVS_C_H__ */
