/*  
 *  摘    要:	
 *		完成视频和音频的解码显示播放和同步功能.
 */

#ifndef __VARENDER_H__
#define __VARENDER_H__

#define VARENDER_VERSION			"v2.0.20.0212"	//库的版本

//错误码定义
#define VARENDER_E_OK				0	//成功
#define VARENDER_E_WOULDBLOCK		1	//操作无法立即执行
#define VARENDER_E_UNKOWN			-1	//未知错误
#define VARENDER_E_TIMER			-4	//创建定时器失败
#define VARENDER_E_INVALID			-5	//资源不可用
#define VARENDER_E_CODESHELL		-6	//CodeShell出错
#define VARENDER_E_MALLOC			-7	//分配内存出错
#define VARENDER_E_OVERFLOW			-8	//内存溢出错误
#define VARENDER_E_PARAM			-9	//参数错误

//音频输出声道定义
#define VARENDER_CHANNEL_DUAL		0	//双声道输出
#define VARENDER_CHANNEL_LEFT		1	//左声道输出
#define VARENDER_CHANNEL_RIGHT		2	//右声道输出

//裸视频数据格式
#define VARENDER_FORMAT_RGB24		1	//RGB24
#define VARENDER_FORMAT_YUV420		2	//YUV420

//播放模式
#define VARENDER_PLAYMODE_REPLAY	0	//回放模式
#define VARENDER_PLAYMODE_REALTIME	1	//实时模式

//旋转模式
#define VARENDER_ROTATE_0			0	//不旋转
#define VARENDER_ROTATE_90			1	//旋转90度
#define VARENDER_ROTATE_180		2	//旋转180度
#define VARENDER_ROTATE_270		3	//旋转270度

//录像和抓拍文件名的最大长度
#define VARENDER_MAXLEN_FILENAME	256

#ifdef WIN32
	#define VARENDER_STDCALL __stdcall
	#ifdef VARENDER_EXPORTS
		#define VARENDER_PORT __declspec(dllexport)
	#else
		#define VARENDER_PORT
	#endif
#else
	#define VARENDER_STDCALL
	#define VARENDER_PORT
#endif
#define VARENDER_API VARENDER_PORT VARENDER_STDCALL

//各种句柄定义
typedef void* VARENDERUSER_HANDLE;
typedef void* VARENDER_HANDLE;
typedef void* VARENDER_HWND;
typedef void* VARENDER_HDC;


/*  功能描述: 显示图像的时,自定义绘图的回调函数接口
 *  参数说明:
 *		VARENDERUSER_HANDLE hUser [IN]:			自定义用户数据
 *		VARENDER_HDC hDC [IN]:					图像口DC
 *      int X [IN]:								图像区域的X坐标
 *      int Y [IN]:								图像区域的Y坐标
 *      int nWidth [IN]:						图像区域的宽度
 *      int nHeight [IN]:						图像区域的高度
 *      int X2 [IN]:							显示区域的X坐标
 *      int Y2 [IN]:							显示区域的Y坐标
 *      int nWidth2 [IN]:						显示区域的宽度
 *      int nHeight2 [IN]:						显示区域的高度
 */
typedef void (VARENDER_STDCALL *VARENDER_DISPLAY_CALLBACK)(VARENDERUSER_HANDLE hUser, VARENDER_HDC hDC, 
										  int X, int Y, int nWidth, int nHeight,
										  int X2, int Y2, int nWidth2, int nHeight2);

/*  功能描述: 视频解码后的数据的回调函数
 *  参数说明:
 *		VARENDERUSER_HANDLE hUser [IN]:			自定义用户数据
 *      int nWidth [IN]:						视频的宽度
 *      int nHeight [IN]:						视频的高度
 *      *pBuf [IN]:								视频数据的缓冲地址
 *      int iBufLen [IN]:						视频数据的长度
 *      char cFormat [IN]:						视频数据的格式,见前面的宏定义
 */
typedef void (VARENDER_STDCALL *VARENDER_VIDEO_CALLBACK)(VARENDERUSER_HANDLE hUser, int nWidth, int nHeight, char *pBuf, int iBufLen, char cFormat);

/*  功能描述: 音频解码后的数据的回调函数
 *  参数说明:
 *      VARENDERUSER_HANDLE hUser [IN]:			自定义用户数据
 *      short *pPCMBuf [IN]:					PCM音频数据缓冲
 *      int nSampleNum [IN]:					PCM音频样本数
 *  返回值: typedef void 
 *  备注:	
 */
typedef void (VARENDER_STDCALL *VARENDER_AUDIO_CALLBACK)(VARENDERUSER_HANDLE hUser, char *pBuf, int iBufLen, int BitsPerSample, int iSampleRate, int iLRChannel);

#ifdef __cplusplus
extern "C" {
#endif

/*  功能描述: 初始化VAReander库
 *  参数说明:
 *      const char *cpszDLLPath [OUT]:	外部音视频解码库的路径,传入NULL表示使用内嵌的解码库.
 *  返回值: 错误码,见前面的宏定义
 *  备注: 程序启动的时候必须先初始化才能够调用其他函数,全局调用一次即可.
 */
int VARENDER_API VARender_Startup(const char *cpszDLLPath);

/*  功能描述: 清除VARender库
 *  备注: 程序退出之前调用此函数,否则可能造成资源泄漏
 */
void VARENDER_API VARender_Cleanup();

/*  功能描述: 创建VARender对象
 *  参数说明:
 *      VARENDER_HANDLE *phVARender [OUT]:	创建得到的对象句柄
 *  返回值: 错误码,见前面的宏定义
 *	备注: 创建出来的句柄必须使用VARender_Close关闭,否则会造成内存泄漏
 */
int VARENDER_API VARender_Open(VARENDER_HANDLE *phVARender);

/*  功能描述: 关闭VARender对象
 */
void VARENDER_API VARender_Close(VARENDER_HANDLE hVARender);

/*  功能描述: 启用/禁用硬解码（缺省不启用）
 *  参数说明:
 *      int bEnable [IN]:					1表示启用硬解码，0表示使用软解码。
 *  返回值: 错误码,见前面的宏定义
 *	备注：启用硬解码CPU会少耗些，但是有些电脑可能无法使用。
 */
int VARENDER_API VARender_EnableHA(VARENDER_HANDLE hVARender, int bEnable);

/*  功能描述: 启用/禁用刷新功能（缺省启用）
 *  参数说明:
 *      int bEnable [IN]:					1表示启用刷新功能，0表示禁用刷新功能。
 *	备注：启用刷新会多拷贝一次内存。但是不启用的话，窗口重绘的时候，就没有图像了。
 */
void VARENDER_API VARender_EnableRefresh(VARENDER_HANDLE hVARender, int bEnable);

/*  功能描述: 设置自定义绘图回调函数
 *  参数说明:
 *      VARENDER_CALLBACK pCallBack [IN]:	绘图回调函数
 *      VARENDER_HANDLE hUser [IN]:			自定义用户数据
 */
void VARENDER_API VARender_SetDisplayCallBack(VARENDER_HANDLE hVARender, VARENDER_DISPLAY_CALLBACK pCallBack, VARENDERUSER_HANDLE hUser);

/*  功能描述: 设置接收视频解码后的数据的回调函数
 *  参数说明:
 *      VARENDER_CALLBACK pCallBack [IN]:	接收裸视频数据的回调函数
 *      VARENDER_HANDLE hUser [IN]:			自定义用户数据
 *		char cFormat [IN]:					需要的裸数据格式,可以支持RGB24和YUV420格式
 */
void VARENDER_API VARender_SetVideoCallBack(VARENDER_HANDLE hVARender, VARENDER_VIDEO_CALLBACK pCallBack, VARENDERUSER_HANDLE hUser, char cFormat);

/*  功能描述: 设置接收音频解码后的数据的回调函数
 *  参数说明:
 *      VARENDER_AUDIO_CALLBACK pCallBack [IN]:	音频数据回调函数
 *      VARENDER_HANDLE hUser [IN]:				自定义用户数据
 */
void VARENDER_API VARender_SetAudioCallBack(VARENDER_HANDLE hVARender, VARENDER_AUDIO_CALLBACK pCallBack, VARENDERUSER_HANDLE hUser);

/*  功能描述: 设置音频输出声道
 *  参数说明:
 *      int iLRChannel [IN]:			输出的声道,取值见前面的宏定义
 *  备注: 缺省是两个声道都输出
 *		  必须在Open之后,塞入数据之前调用这个函数,之后不能调用这个函数了,否则会出现内存访问冲突
 */
void VARENDER_API VARender_SetAudioLRChannel(VARENDER_HANDLE hVARender, int iLRChannel);

/*  功能描述: 设置显示视频的显示器编号
 *  参数说明:
 *		int iNo [IN]:				显示器的编号,从0(默认显示器)开始,到系统支持的最大显示器数目
 *		int iX [IN]:				显示器的屏幕左上角X坐标,多个显示器组成一个大桌面的时候,这个显示器的坐标.
 *		int iY [IN]:				显示器的屏幕左上角Y坐标,多个显示器组成一个大桌面的时候,这个显示器的坐标.
 *  返回值: 错误码,见前面的宏定义
 *  备注: 多个显示器并且使用DDraw的时候,需要设置这个.
 *		  建议先调用VARender_SetMonitor,再调用VARender_SetWindow
 */
int VARENDER_API VARender_SetMonitor(VARENDER_HANDLE hVARender, int iNo, int iX, int iY);

/*  功能描述: 设置显示窗口句柄
 *  参数说明:
 *		VARENDER_HWND hWindow [IN]:		显示窗口句柄,传入NULL表示释放窗口
 *  返回值: 错误码,见前面的宏定义
 *	备注:
 *		在调用VARender_PumpFrame函数之前,必须先调用此函数设置窗口句柄.
 *		如果没有设置句柄,将显示不了图像
 */
int VARENDER_API VARender_SetWindow(VARENDER_HANDLE hVARender, VARENDER_HWND hWnd);

/*  功能描述: 设置是否固定原始比例显示
 *  参数说明:
 *		int bFixRatio [IN]:				是否固定原始比例显示
 *	备注: 默认是不按比例显示，也就是根据窗口拉伸的。
 */
void VARENDER_API VARender_SetFixAspectRatio(VARENDER_HANDLE hVARender, int bFixRatio);

/*  功能描述: 设置竖屏时是否自动按比例显示
 *  参数说明:
 *		int bAutoFixRatio [IN]:			竖屏时是否自动按比例显示
 *	备注: 默认启用这个功能，避免竖屏时拉伸太难看。
 */
void VARENDER_API VARender_SetAutoFixAspectRatio(VARENDER_HANDLE hVARender, int bAutoFixRatio);

/*  功能描述: 设置旋转模式
 *  参数说明:
 *		int iRotateMode [IN]:			旋转模式，见前面的宏定义
 *	备注: 默认为不旋转模式。
 */
void VARENDER_API VARender_SetRotateMode(VARENDER_HANDLE hVARender, int iRotateMode);

/*  功能描述: 设置窗口中的显示区域
 *  参数说明:
 *      int XDest [IN]:					x-coordinate of destination upper-left corner
 *      int YDest [IN]:					y-coordinate of destination upper-left corner
 *      int nDestWidth [IN]:			width of destination rectangle
 *      int nDestHeight [IN]:			height of destination rectangle
 *	备注: 默认的目标x,y为0,宽度和高度为窗口的宽度和高度
 */
void VARENDER_API VARender_SetDestRect(VARENDER_HANDLE hVARender, int XDest, int YDest, int nDestWidth, int nDestHeight);

/*  功能描述: 设置图像的显示区域(局部电子放大)
 *  参数说明:
 *      int XSrc [IN]:					x-coordinate of source upper-left corner
 *      int YSrc [IN]:					y-coordinate of source upper-left corner
 *      int nSrcWidth [IN]:				width of source rectangle
 *      int nSrcHeight [IN]:			height of source rectangle
 *	备注: 默认的源x,y为0,宽度和高度为图像实际宽度和高度
 */
void VARENDER_API VARender_SetSrcRect(VARENDER_HANDLE hVARender, int XSrc, int YSrc, int nSrcWidth, int nSrcHeight);

/*  功能描述: 设置是否使用DDraw
 *  参数说明:
 *      int bDDraw [IN]:				是否使DDraw,0表示不使用,1表示使用.
 *  返回值: 错误码,见前面的宏定义
 *  备注: 如果不调用此函数,默认为不使用DDraw
 *		  建议先调用VARender_SetDDraw,再调用VARender_SetWindow
 */
int VARENDER_API VARender_SetDDraw(VARENDER_HANDLE hVARender, int bDDraw);

/*  功能描述: 获取是否使用DDraw
 *  返回值: 是否使DDraw,0表示不使用,1表示使用
 */
int VARENDER_API VARender_IsDDraw(VARENDER_HANDLE hVARender);

/*  功能描述: 开始/停止 播放/显示 视频/音频
 *  备注: 
 *		开始视频则显示视频,否则只解码,不显示视频
 *		开始音频则播放音频,否则不解码,不播放音频
 */
void VARENDER_API VARender_StartVideo(VARENDER_HANDLE hVARender);
void VARENDER_API VARender_StopVideo(VARENDER_HANDLE hVARender);
void VARENDER_API VARender_StartAudio(VARENDER_HANDLE hVARender);
void VARENDER_API VARender_StopAudio(VARENDER_HANDLE hVARender);

/*  功能描述: 塞入视频数据帧(带存储帧头)
 *  参数说明:
 *		char *pFrame [IN]:				数据帧缓冲.存储帧头开始
 *		int iLen [IN]					数据帧长度
 *	返回值: VARENDER_E_OK			表示成功
 *			VARENDER_E_WOULDBLOCK	表示数据缓冲满,需要继续尝试塞入
 *	备注:　如果检测到安装了外部解码库,则使用外部解码库.
 *		   如果没有检测到安装的外部解码库,则使用内部自带解码库.
 */
int VARENDER_API VARender_PumpVideoFrame(VARENDER_HANDLE hVARender, char *pFrame, int iLen);

/*  功能描述: 塞入伴音音频数据帧(带存储帧头)
 *  参数说明:
 *		char *pFrame [IN]:				数据帧缓冲.存储帧头开始
 *		int iLen [IN]					数据帧长度
 *	返回值: VARENDER_E_OK			表示成功
 *			VARENDER_E_WOULDBLOCK	表示数据缓冲满,需要继续尝试塞入
 *	备注:　如果检测到安装了外部解码库,则使用外部解码库.
 *		   如果没有检测到安装的外部解码库,则使用内部自带解码库.
 */
int VARENDER_API VARender_PumpAudioFrame(VARENDER_HANDLE hVARender, char *pFrame, int iLen);

/*  功能描述: 塞入喊话音频数据帧(带存储帧头)
 *  参数说明:
 *		char *pFrame [IN]:				数据帧缓冲.存储帧头开始
 *		int iLen [IN]					数据帧长度
 *	备注:　这个函数纯粹就是为了在录像的时候，能够把本地的音频也录进去而加的。
 */
void VARENDER_API VARender_PumpCallAudioFrame(VARENDER_HANDLE hVARender, char *pFrame, int iLen);

/*  功能描述: 抓图
 *  参数说明:
 *      const char *pszFileName [IN]:	抓拍文件保存的文件名(必须以.bmp或者.jpg为后缀名)
 *	返回值: 参看宏定义
 */
int VARENDER_API VARender_Snapshot(VARENDER_HANDLE hVARender, const char *pszFileName);

/*  功能描述: 抓图到内存
 *  参数说明:
 *      char *pBuffer [IN]:	抓拍图片保存的内存地址。缓冲尽量大点，如果太小会返回VARENDER_E_OVERFLOW
 *		int *piBufferLen [IN,OUT]: 输入的时候是抓拍图片的内存缓冲长度，输出的是实际图片数据的长度。
 *		const char *cpszExt [IN]: 格式后缀，目前仅仅支持：“jpg"。
 *		int *piWidth [OUT]: 图片的宽。
 *		int *piHeight [OUT]: 图片的高。
 *	返回值: 参看宏定义
 *	说明: 这个函数不能两个地方同时调用，如果有一个没返回，另外一个地方调用会返回：VARENDER_E_WOULDBLOCK。
 */
int VARENDER_API VARender_SnapshotMem(VARENDER_HANDLE hVARender, char *pBuffer, int *piBufferLen, const char *cpszExt, int *piWidth, int *piHeight);

/*  功能描述: 重绘最后一幅图像
 *  备注: 在显示窗口刷新的时候调用这个函数,如果还未显示数据,调此函数会出现黑屏
 */
void VARENDER_API VARender_Refresh(VARENDER_HANDLE hVARender);

/*  功能描述: 设置当前视频是否精确同步播放
 */
void VARENDER_API VARender_SetSync(VARENDER_HANDLE hVARender, int bSync);

/*  功能描述: 获取当前视频是否精确同步播放
 *  返回值: 是否精确同步播放
 */
int VARENDER_API VARender_IsSync(VARENDER_HANDLE hVARender);

/*  功能描述: 设置播放模式
 *  参数说明:
 *      int iMode [IN]:		播放模式,取值见前面的VARENDER_PLAYMODE_XXX宏定义
 *  备注: 实时模式时:
 *			1.会根据缓冲的数据大小来动态调节播放的速度.
 *			2.音视频是否精确同步根据VARender_SetSync函数来定.默认是不精确同步的.
 *		  回放模式时:
 *			1.严格按照时间戳,按照原始速度来播放,并且音视频精确同步.
 *			2.可以通过VARender_SetSpeed来按整数倍改变播放速度.
 *			3.此模式的时候,内部缓冲的帧数会比较少,需要上层及时塞入数据
 */
void VARENDER_API VARender_SetPlayMode(VARENDER_HANDLE hVARender, int iMode);

/*  功能描述: 获取当前的播放模式
 *  返回值: 当前的播放模式
 */
int VARENDER_API VARender_GetPlayMode(VARENDER_HANDLE hVARender);

/*  功能描述: 设置播放速度
 *  参数说明:
 *      int iSpeed [IN]:	播放速度的指数,底数为2,比如:
 *								0表示2的0次方,1倍速,正常速度
 *								-1表示2的-1次方,1/2倍数
 *								1表示2的1次方,为2倍数
 *	备注: 只有在回放模式时有效.
 *		  播放速度不是正常速度的时候,会自动停止音频的播放.
 */
void VARENDER_API VARender_SetSpeed(VARENDER_HANDLE hVARender, int iSpeed);

/*  功能描述: 获取当前播放速度
 *  返回值: 当前播放速度
 */
int VARENDER_API VARender_GetSpeed(VARENDER_HANDLE hVARender);

/*  功能描述: 获取/设置音频播放音量,范围0-100
 */
int VARENDER_API VARender_GetVolume(VARENDER_HANDLE hVARender);
void VARENDER_API VARender_SetVolume(VARENDER_HANDLE hVARender, int iVolume);

/*  功能描述：设置缓冲时间，
 *  参数说明：
 *      int iBufferTime [IN]:		缓冲时间，单位毫秒。
 *备注：	这个时间如果等于最大网络抖动时间，延时和连贯性都会最优。
 */
void VARENDER_API VARender_SetBufferTime(VARENDER_HANDLE hVARender, int iBufferTime);

//////////////////////////////////////////////////////////////////////////
//	获取辅助统计信息的
//////////////////////////////////////////////////////////////////////////

/*  功能描述: 开始/停止录像
 *  参数说明:
 *      const char *lpszFileName [IN]:		文件名(必须以.avi为后缀),最大长度不可大于VARENDER_MAXLEN_FILENAME.
 *      unsigned int uiMaxFileTime [IN]:	录像文件的最大时间长度,单位毫秒.超过长度会自动换文件
 *  返回值: 见上面宏定义.
 *	备注: 生成的文件名自动加后缀"_00",换文件的时候,递增,"_01","_02",...
 */
int VARENDER_API VARender_StartRecord(VARENDER_HANDLE hVARender, const char *lpszFileName, unsigned int uiMaxFileTime);
void VARENDER_API VARender_CloseRecord(VARENDER_HANDLE hVARender);

/*  功能描述: 设置录像附加信息文件信息
 *  参数说明:
 *      char *pszPUID [IN]:		设备的PUID
 *      int iResIdx [IN]:		录像资源的编号
 *      char *pszResType [IN]:	录像资源的类型
 *	备注: 如果调用了这个函数,录像的时候,就会对应生成一个lfi文件.
 */
void VARENDER_API VARender_SetLfiFileInfo(VARENDER_HANDLE hVARender, char *pszPUID, int iResIdx, char *pszResType);

//////////////////////////////////////////////////////////////////////////
//	获取辅助统计信息的函数
//////////////////////////////////////////////////////////////////////////

/*  功能描述: 获取当前视频的帧率
 *  返回值: 当前视频的帧率
 *	备注:	第一个函数是*5/4的版本，第二个函数是实际帧率。
 */
int VARENDER_API VARender_GetFrameRate(VARENDER_HANDLE hVARender);
int VARENDER_API VARender_GetFrameRateReal(VARENDER_HANDLE hVARender);

/*  功能描述: 获取当前视频的码率
 *  返回值: 当前视频的码率
 *	备注:	第一个函数是*4/5的版本，第二个函数是实际码率。
 */
int VARENDER_API VARender_GetBitRate(VARENDER_HANDLE hVARender);
int VARENDER_API VARender_GetBitRateReal(VARENDER_HANDLE hVARender);

/*  功能描述: 获取最近播放的视频/音频帧的时间戳
 *  参数说明:
 *      unsigned int *puiTimeStamp [OUT]:	最近播放的时间戳
 *  返回值: VARENDER_E_OK			表示成功
 *			VARENDER_E_INVALID		还没有播放帧
 */
int VARENDER_API VARender_GetLatestPlayVideoTimeStamp(VARENDER_HANDLE hVARender, unsigned int *puiTimeStamp);
int VARENDER_API VARender_GetLatestPlayAudioTimeStamp(VARENDER_HANDLE hVARender, unsigned int *puiTimeStamp);

/*  功能描述: 获取当前视频音频缓冲链表长度等调试参数
 */
int VARENDER_API VARender_GetVideoListLen(VARENDER_HANDLE hVARender);
int VARENDER_API VARender_GetAudioListLen(VARENDER_HANDLE hVARender);
int VARENDER_API VARender_GetVADelta(VARENDER_HANDLE hVARender);
int VARENDER_API VARender_GetSilenceAudioFrameNum(VARENDER_HANDLE hVARender);
int VARENDER_API VARender_GetDropAudioFrameNum(VARENDER_HANDLE hVARender);
int VARENDER_API VARender_GetVideoBufferBytes(VARENDER_HANDLE hVARender, int *piMaxBufferBytes);
int VARENDER_API VARender_GetAudioBufferFrames(VARENDER_HANDLE hVARender, int *piMaxBufferFrames);

#ifdef __cplusplus
}
#endif

#endif //__VARENDER_H__
