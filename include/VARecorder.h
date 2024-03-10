#ifndef __VARECORDER_H__
#define __VARECORDER_H__

#define VARECORDER_VERSION				"v2.0.17.809"	//库的版本

//错误码定义
#define VARECORDER_E_OK					0	//成功
#define VARECORDER_E_WOULDBLOCK			1	//操作无法立即执行
#define VARECORDER_E_UNKOWN				-1	//未知错误
#define VARECORDER_E_FRAMEINFOCHANGE	-2	//帧信息发生改变
#define VARECORDER_E_UNKOWNFRAMEINFO	-3	//不支持的帧信息
#define VARECORDER_E_MALLOC				-4	//分配内存失败

typedef void* VARECORDER_HANDLE;

#ifdef WIN32
	#define VARECORDER_STDCALL __stdcall
	#ifdef VARECORDER_EXPORTS
		#define VARECORDER_PORT __declspec(dllexport)
	#else
		#define VARECORDER_PORT
	#endif
#else
	#define VARECORDER_STDCALL
	#define VARECORDER_PORT
#endif
#define VARECORDER_API VARECORDER_PORT VARECORDER_STDCALL

#ifdef __cplusplus
extern "C" {
#endif

/*  功能描述: 初始化VAReander库
 *  参数说明:
 *      const char *cpszDLLPath [OUT]:	外部音视频解码库的路径,传入NULL表示使用内嵌的解码库.
 *  返回值: 错误码,见前面的宏定义
 *  备注: 程序启动的时候必须先初始化才能够调用其他函数,全局调用一次即可.
 */
int VARECORDER_API VARecorder_Startup(const char *cpszDLLPath);

/*  功能描述: 清除VARender库
 *  备注: 程序退出之前调用此函数,否则可能造成资源泄漏
 */
void VARECORDER_API VARecorder_Cleanup();

/*  功能描述: 创建VARecorder对象
 *  参数说明:
 *		const char *lpszFileName [in]: 录像文件名
 *      VARECORDER_HANDLE *phVARecorder [OUT]:	创建得到的对象句柄
 *  返回值: 错误码,见前面的宏定义
 */
int VARECORDER_API VARecorder_Open(const char *lpszFileName, VARECORDER_HANDLE *phVARecorder);

/*  功能描述: 关闭VARender对象
 *  参数说明:
 *      VARECORDER_HANDLE hVARecorder [IN]:	VARender对象句柄
 */
void VARECORDER_API VARecorder_Close(VARECORDER_HANDLE hVARecorder);

/*  功能描述: 设置仅仅存音频
 *  参数说明:
 *      VARECORDER_HANDLE hVARecorder [IN]:	VARender对象句柄
 */
void VARECORDER_API VARecorder_SetAudioOnly(VARECORDER_HANDLE hVARecorder);

/*  功能描述: 塞入视频数据（从存储帧头开始）
 *  参数说明:
 *      VARECORDER_HANDLE hVARecorder [IN]:	VARender对象句柄
 *		char *pFrame [IN]:				数据帧缓冲.
 *		int iLen [IN]					数据帧长度
 *	返回值,错误码,见前面的宏定义,可能返回如下错误码:
 *			VARECORDER_E_FRAMEINFOCHANGE	帧信息发生改变,上层需要更换文件
 *			VARECORDER_E_UNKOWNFRAMEINFO	可能图像大小,算法等不支持
 */
int VARECORDER_API VARecorder_PumpVideoFrame(VARECORDER_HANDLE hVARecorder, char *pFrame, int iLen);

/*  功能描述: 塞入伴音音频数据（从存储帧头开始）
 *  参数说明:
 *      VARECORDER_HANDLE hVARecorder [IN]:	VARender对象句柄
 *		char *pFrame [IN]:				数据帧缓冲.
 *		int iLen [IN]					数据帧长度
 *	返回值,错误码,见前面的宏定义,可能返回如下错误码:
 *			VARECORDER_E_FRAMEINFOCHANGE	帧信息发生改变,上层需要更换文件
 *			VARECORDER_E_UNKOWNFRAMEINFO	可能视频算法不支持,数据长度不正确
 */
int VARECORDER_API VARecorder_PumpAudioFrame(VARECORDER_HANDLE hVARecorder, char *pFrame, int iLen);

/*  功能描述: 塞入喊话音频数据（从存储帧头开始）
 *  参数说明:
 *      VARECORDER_HANDLE hVARecorder [IN]:	VARender对象句柄
 *		char *pFrame [IN]:				数据帧缓冲.
 *		int iLen [IN]					数据帧长度
 *	返回值,错误码,见前面的宏定义,可能返回如下错误码:
 *			VARECORDER_E_FRAMEINFOCHANGE	帧信息发生改变,上层需要更换文件
 *			VARECORDER_E_UNKOWNFRAMEINFO	可能视频算法不支持,数据长度不正确
 */
int VARECORDER_API VARecorder_PumpCallAudioFrame(VARECORDER_HANDLE hVARecorder, char *pFrame, int iLen);

#ifdef __cplusplus
}
#endif

#endif //__VARECORDER_H__
