#ifndef __ICVS_S_H__
#define __ICVS_S_H__

#include "iCVSC_base.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 通过PUID获取设备接入密码的回调函数 */
typedef int (WINAPI *GET_PSW_BY_PUID)(void *hUser, const char *pszPUID, unsigned char szPasswordHash[16]);

/* 启动服务 */
IC_API int WINAPI IC_StartService(const char *pszServiceIP, int nListenPort, int nStreamPort, const char *pszBindIP, 
								  GET_PSW_BY_PUID pGetPswByPUID, void *hUser);
/* 停止服务 */
IC_API int WINAPI IC_StopService(void);

/* 设置保活间隔*/ 
// 在IC_StartService后调用 int iKAInterval [IN]:(单位:秒， 默认15，最大不能超过60）
IC_API int WINAPI IC_SetKeepAliveInterval(int iKAInterval);

/* 接受并添加一个设备 */
IC_API int WINAPI IC_AcceptSession(IC_HANDLE *hSession);
/* 删除一个设备 */
IC_API int WINAPI IC_DeleteSession(IC_HANDLE hSession);

#ifdef __cplusplus
}
#endif

#endif /* __ICVS_S_H__ */
