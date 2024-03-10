#ifndef __ICVS_S_H__
#define __ICVS_S_H__

#include "iCVSC_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ͨ��PUID��ȡ�豸��������Ļص����� */
typedef int (WINAPI *GET_PSW_BY_PUID)(void *hUser, const char *pszPUID, unsigned char szPasswordHash[16]);

/* �������� */
IC_API int WINAPI IC_StartService(const char *pszServiceIP, int nListenPort, int nStreamPort, const char *pszBindIP, 
								  GET_PSW_BY_PUID pGetPswByPUID, void *hUser);
/* ֹͣ���� */
IC_API int WINAPI IC_StopService(void);

/* ���ñ�����*/ 
// ��IC_StartService����� int iKAInterval [IN]:(��λ:�룬 Ĭ��15������ܳ���60��
IC_API int WINAPI IC_SetKeepAliveInterval(int iKAInterval);

/* ���ܲ����һ���豸 */
IC_API int WINAPI IC_AcceptSession(IC_HANDLE *hSession);
/* ɾ��һ���豸 */
IC_API int WINAPI IC_DeleteSession(IC_HANDLE hSession);

#ifdef __cplusplus
}
#endif

#endif /* __ICVS_S_H__ */
