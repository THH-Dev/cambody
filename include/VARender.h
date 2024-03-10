/*  
 *  ժ    Ҫ:	
 *		�����Ƶ����Ƶ�Ľ�����ʾ���ź�ͬ������.
 */

#ifndef __VARENDER_H__
#define __VARENDER_H__

#define VARENDER_VERSION			"v2.0.20.0212"	//��İ汾

//�����붨��
#define VARENDER_E_OK				0	//�ɹ�
#define VARENDER_E_WOULDBLOCK		1	//�����޷�����ִ��
#define VARENDER_E_UNKOWN			-1	//δ֪����
#define VARENDER_E_TIMER			-4	//������ʱ��ʧ��
#define VARENDER_E_INVALID			-5	//��Դ������
#define VARENDER_E_CODESHELL		-6	//CodeShell����
#define VARENDER_E_MALLOC			-7	//�����ڴ����
#define VARENDER_E_OVERFLOW			-8	//�ڴ��������
#define VARENDER_E_PARAM			-9	//��������

//��Ƶ�����������
#define VARENDER_CHANNEL_DUAL		0	//˫�������
#define VARENDER_CHANNEL_LEFT		1	//���������
#define VARENDER_CHANNEL_RIGHT		2	//���������

//����Ƶ���ݸ�ʽ
#define VARENDER_FORMAT_RGB24		1	//RGB24
#define VARENDER_FORMAT_YUV420		2	//YUV420

//����ģʽ
#define VARENDER_PLAYMODE_REPLAY	0	//�ط�ģʽ
#define VARENDER_PLAYMODE_REALTIME	1	//ʵʱģʽ

//��תģʽ
#define VARENDER_ROTATE_0			0	//����ת
#define VARENDER_ROTATE_90			1	//��ת90��
#define VARENDER_ROTATE_180		2	//��ת180��
#define VARENDER_ROTATE_270		3	//��ת270��

//¼���ץ���ļ�������󳤶�
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

//���־������
typedef void* VARENDERUSER_HANDLE;
typedef void* VARENDER_HANDLE;
typedef void* VARENDER_HWND;
typedef void* VARENDER_HDC;


/*  ��������: ��ʾͼ���ʱ,�Զ����ͼ�Ļص������ӿ�
 *  ����˵��:
 *		VARENDERUSER_HANDLE hUser [IN]:			�Զ����û�����
 *		VARENDER_HDC hDC [IN]:					ͼ���DC
 *      int X [IN]:								ͼ�������X����
 *      int Y [IN]:								ͼ�������Y����
 *      int nWidth [IN]:						ͼ������Ŀ��
 *      int nHeight [IN]:						ͼ������ĸ߶�
 *      int X2 [IN]:							��ʾ�����X����
 *      int Y2 [IN]:							��ʾ�����Y����
 *      int nWidth2 [IN]:						��ʾ����Ŀ��
 *      int nHeight2 [IN]:						��ʾ����ĸ߶�
 */
typedef void (VARENDER_STDCALL *VARENDER_DISPLAY_CALLBACK)(VARENDERUSER_HANDLE hUser, VARENDER_HDC hDC, 
										  int X, int Y, int nWidth, int nHeight,
										  int X2, int Y2, int nWidth2, int nHeight2);

/*  ��������: ��Ƶ���������ݵĻص�����
 *  ����˵��:
 *		VARENDERUSER_HANDLE hUser [IN]:			�Զ����û�����
 *      int nWidth [IN]:						��Ƶ�Ŀ��
 *      int nHeight [IN]:						��Ƶ�ĸ߶�
 *      *pBuf [IN]:								��Ƶ���ݵĻ����ַ
 *      int iBufLen [IN]:						��Ƶ���ݵĳ���
 *      char cFormat [IN]:						��Ƶ���ݵĸ�ʽ,��ǰ��ĺ궨��
 */
typedef void (VARENDER_STDCALL *VARENDER_VIDEO_CALLBACK)(VARENDERUSER_HANDLE hUser, int nWidth, int nHeight, char *pBuf, int iBufLen, char cFormat);

/*  ��������: ��Ƶ���������ݵĻص�����
 *  ����˵��:
 *      VARENDERUSER_HANDLE hUser [IN]:			�Զ����û�����
 *      short *pPCMBuf [IN]:					PCM��Ƶ���ݻ���
 *      int nSampleNum [IN]:					PCM��Ƶ������
 *  ����ֵ: typedef void 
 *  ��ע:	
 */
typedef void (VARENDER_STDCALL *VARENDER_AUDIO_CALLBACK)(VARENDERUSER_HANDLE hUser, char *pBuf, int iBufLen, int BitsPerSample, int iSampleRate, int iLRChannel);

#ifdef __cplusplus
extern "C" {
#endif

/*  ��������: ��ʼ��VAReander��
 *  ����˵��:
 *      const char *cpszDLLPath [OUT]:	�ⲿ����Ƶ������·��,����NULL��ʾʹ����Ƕ�Ľ����.
 *  ����ֵ: ������,��ǰ��ĺ궨��
 *  ��ע: ����������ʱ������ȳ�ʼ�����ܹ�������������,ȫ�ֵ���һ�μ���.
 */
int VARENDER_API VARender_Startup(const char *cpszDLLPath);

/*  ��������: ���VARender��
 *  ��ע: �����˳�֮ǰ���ô˺���,������������Դй©
 */
void VARENDER_API VARender_Cleanup();

/*  ��������: ����VARender����
 *  ����˵��:
 *      VARENDER_HANDLE *phVARender [OUT]:	�����õ��Ķ�����
 *  ����ֵ: ������,��ǰ��ĺ궨��
 *	��ע: ���������ľ������ʹ��VARender_Close�ر�,���������ڴ�й©
 */
int VARENDER_API VARender_Open(VARENDER_HANDLE *phVARender);

/*  ��������: �ر�VARender����
 */
void VARENDER_API VARender_Close(VARENDER_HANDLE hVARender);

/*  ��������: ����/����Ӳ���루ȱʡ�����ã�
 *  ����˵��:
 *      int bEnable [IN]:					1��ʾ����Ӳ���룬0��ʾʹ������롣
 *  ����ֵ: ������,��ǰ��ĺ궨��
 *	��ע������Ӳ����CPU���ٺ�Щ��������Щ���Կ����޷�ʹ�á�
 */
int VARENDER_API VARender_EnableHA(VARENDER_HANDLE hVARender, int bEnable);

/*  ��������: ����/����ˢ�¹��ܣ�ȱʡ���ã�
 *  ����˵��:
 *      int bEnable [IN]:					1��ʾ����ˢ�¹��ܣ�0��ʾ����ˢ�¹��ܡ�
 *	��ע������ˢ�»�࿽��һ���ڴ档���ǲ����õĻ��������ػ��ʱ�򣬾�û��ͼ���ˡ�
 */
void VARENDER_API VARender_EnableRefresh(VARENDER_HANDLE hVARender, int bEnable);

/*  ��������: �����Զ����ͼ�ص�����
 *  ����˵��:
 *      VARENDER_CALLBACK pCallBack [IN]:	��ͼ�ص�����
 *      VARENDER_HANDLE hUser [IN]:			�Զ����û�����
 */
void VARENDER_API VARender_SetDisplayCallBack(VARENDER_HANDLE hVARender, VARENDER_DISPLAY_CALLBACK pCallBack, VARENDERUSER_HANDLE hUser);

/*  ��������: ���ý�����Ƶ���������ݵĻص�����
 *  ����˵��:
 *      VARENDER_CALLBACK pCallBack [IN]:	��������Ƶ���ݵĻص�����
 *      VARENDER_HANDLE hUser [IN]:			�Զ����û�����
 *		char cFormat [IN]:					��Ҫ�������ݸ�ʽ,����֧��RGB24��YUV420��ʽ
 */
void VARENDER_API VARender_SetVideoCallBack(VARENDER_HANDLE hVARender, VARENDER_VIDEO_CALLBACK pCallBack, VARENDERUSER_HANDLE hUser, char cFormat);

/*  ��������: ���ý�����Ƶ���������ݵĻص�����
 *  ����˵��:
 *      VARENDER_AUDIO_CALLBACK pCallBack [IN]:	��Ƶ���ݻص�����
 *      VARENDER_HANDLE hUser [IN]:				�Զ����û�����
 */
void VARENDER_API VARender_SetAudioCallBack(VARENDER_HANDLE hVARender, VARENDER_AUDIO_CALLBACK pCallBack, VARENDERUSER_HANDLE hUser);

/*  ��������: ������Ƶ�������
 *  ����˵��:
 *      int iLRChannel [IN]:			���������,ȡֵ��ǰ��ĺ궨��
 *  ��ע: ȱʡ���������������
 *		  ������Open֮��,��������֮ǰ�����������,֮���ܵ������������,���������ڴ���ʳ�ͻ
 */
void VARENDER_API VARender_SetAudioLRChannel(VARENDER_HANDLE hVARender, int iLRChannel);

/*  ��������: ������ʾ��Ƶ����ʾ�����
 *  ����˵��:
 *		int iNo [IN]:				��ʾ���ı��,��0(Ĭ����ʾ��)��ʼ,��ϵͳ֧�ֵ������ʾ����Ŀ
 *		int iX [IN]:				��ʾ������Ļ���Ͻ�X����,�����ʾ�����һ���������ʱ��,�����ʾ��������.
 *		int iY [IN]:				��ʾ������Ļ���Ͻ�Y����,�����ʾ�����һ���������ʱ��,�����ʾ��������.
 *  ����ֵ: ������,��ǰ��ĺ궨��
 *  ��ע: �����ʾ������ʹ��DDraw��ʱ��,��Ҫ�������.
 *		  �����ȵ���VARender_SetMonitor,�ٵ���VARender_SetWindow
 */
int VARENDER_API VARender_SetMonitor(VARENDER_HANDLE hVARender, int iNo, int iX, int iY);

/*  ��������: ������ʾ���ھ��
 *  ����˵��:
 *		VARENDER_HWND hWindow [IN]:		��ʾ���ھ��,����NULL��ʾ�ͷŴ���
 *  ����ֵ: ������,��ǰ��ĺ궨��
 *	��ע:
 *		�ڵ���VARender_PumpFrame����֮ǰ,�����ȵ��ô˺������ô��ھ��.
 *		���û�����þ��,����ʾ����ͼ��
 */
int VARENDER_API VARender_SetWindow(VARENDER_HANDLE hVARender, VARENDER_HWND hWnd);

/*  ��������: �����Ƿ�̶�ԭʼ������ʾ
 *  ����˵��:
 *		int bFixRatio [IN]:				�Ƿ�̶�ԭʼ������ʾ
 *	��ע: Ĭ���ǲ���������ʾ��Ҳ���Ǹ��ݴ�������ġ�
 */
void VARENDER_API VARender_SetFixAspectRatio(VARENDER_HANDLE hVARender, int bFixRatio);

/*  ��������: ��������ʱ�Ƿ��Զ���������ʾ
 *  ����˵��:
 *		int bAutoFixRatio [IN]:			����ʱ�Ƿ��Զ���������ʾ
 *	��ע: Ĭ������������ܣ���������ʱ����̫�ѿ���
 */
void VARENDER_API VARender_SetAutoFixAspectRatio(VARENDER_HANDLE hVARender, int bAutoFixRatio);

/*  ��������: ������תģʽ
 *  ����˵��:
 *		int iRotateMode [IN]:			��תģʽ����ǰ��ĺ궨��
 *	��ע: Ĭ��Ϊ����תģʽ��
 */
void VARENDER_API VARender_SetRotateMode(VARENDER_HANDLE hVARender, int iRotateMode);

/*  ��������: ���ô����е���ʾ����
 *  ����˵��:
 *      int XDest [IN]:					x-coordinate of destination upper-left corner
 *      int YDest [IN]:					y-coordinate of destination upper-left corner
 *      int nDestWidth [IN]:			width of destination rectangle
 *      int nDestHeight [IN]:			height of destination rectangle
 *	��ע: Ĭ�ϵ�Ŀ��x,yΪ0,��Ⱥ͸߶�Ϊ���ڵĿ�Ⱥ͸߶�
 */
void VARENDER_API VARender_SetDestRect(VARENDER_HANDLE hVARender, int XDest, int YDest, int nDestWidth, int nDestHeight);

/*  ��������: ����ͼ�����ʾ����(�ֲ����ӷŴ�)
 *  ����˵��:
 *      int XSrc [IN]:					x-coordinate of source upper-left corner
 *      int YSrc [IN]:					y-coordinate of source upper-left corner
 *      int nSrcWidth [IN]:				width of source rectangle
 *      int nSrcHeight [IN]:			height of source rectangle
 *	��ע: Ĭ�ϵ�Դx,yΪ0,��Ⱥ͸߶�Ϊͼ��ʵ�ʿ�Ⱥ͸߶�
 */
void VARENDER_API VARender_SetSrcRect(VARENDER_HANDLE hVARender, int XSrc, int YSrc, int nSrcWidth, int nSrcHeight);

/*  ��������: �����Ƿ�ʹ��DDraw
 *  ����˵��:
 *      int bDDraw [IN]:				�Ƿ�ʹDDraw,0��ʾ��ʹ��,1��ʾʹ��.
 *  ����ֵ: ������,��ǰ��ĺ궨��
 *  ��ע: ��������ô˺���,Ĭ��Ϊ��ʹ��DDraw
 *		  �����ȵ���VARender_SetDDraw,�ٵ���VARender_SetWindow
 */
int VARENDER_API VARender_SetDDraw(VARENDER_HANDLE hVARender, int bDDraw);

/*  ��������: ��ȡ�Ƿ�ʹ��DDraw
 *  ����ֵ: �Ƿ�ʹDDraw,0��ʾ��ʹ��,1��ʾʹ��
 */
int VARENDER_API VARender_IsDDraw(VARENDER_HANDLE hVARender);

/*  ��������: ��ʼ/ֹͣ ����/��ʾ ��Ƶ/��Ƶ
 *  ��ע: 
 *		��ʼ��Ƶ����ʾ��Ƶ,����ֻ����,����ʾ��Ƶ
 *		��ʼ��Ƶ�򲥷���Ƶ,���򲻽���,��������Ƶ
 */
void VARENDER_API VARender_StartVideo(VARENDER_HANDLE hVARender);
void VARENDER_API VARender_StopVideo(VARENDER_HANDLE hVARender);
void VARENDER_API VARender_StartAudio(VARENDER_HANDLE hVARender);
void VARENDER_API VARender_StopAudio(VARENDER_HANDLE hVARender);

/*  ��������: ������Ƶ����֡(���洢֡ͷ)
 *  ����˵��:
 *		char *pFrame [IN]:				����֡����.�洢֡ͷ��ʼ
 *		int iLen [IN]					����֡����
 *	����ֵ: VARENDER_E_OK			��ʾ�ɹ�
 *			VARENDER_E_WOULDBLOCK	��ʾ���ݻ�����,��Ҫ������������
 *	��ע:�������⵽��װ���ⲿ�����,��ʹ���ⲿ�����.
 *		   ���û�м�⵽��װ���ⲿ�����,��ʹ���ڲ��Դ������.
 */
int VARENDER_API VARender_PumpVideoFrame(VARENDER_HANDLE hVARender, char *pFrame, int iLen);

/*  ��������: ���������Ƶ����֡(���洢֡ͷ)
 *  ����˵��:
 *		char *pFrame [IN]:				����֡����.�洢֡ͷ��ʼ
 *		int iLen [IN]					����֡����
 *	����ֵ: VARENDER_E_OK			��ʾ�ɹ�
 *			VARENDER_E_WOULDBLOCK	��ʾ���ݻ�����,��Ҫ������������
 *	��ע:�������⵽��װ���ⲿ�����,��ʹ���ⲿ�����.
 *		   ���û�м�⵽��װ���ⲿ�����,��ʹ���ڲ��Դ������.
 */
int VARENDER_API VARender_PumpAudioFrame(VARENDER_HANDLE hVARender, char *pFrame, int iLen);

/*  ��������: ���뺰����Ƶ����֡(���洢֡ͷ)
 *  ����˵��:
 *		char *pFrame [IN]:				����֡����.�洢֡ͷ��ʼ
 *		int iLen [IN]					����֡����
 *	��ע:����������������Ϊ����¼���ʱ���ܹ��ѱ��ص���ƵҲ¼��ȥ���ӵġ�
 */
void VARENDER_API VARender_PumpCallAudioFrame(VARENDER_HANDLE hVARender, char *pFrame, int iLen);

/*  ��������: ץͼ
 *  ����˵��:
 *      const char *pszFileName [IN]:	ץ���ļ�������ļ���(������.bmp����.jpgΪ��׺��)
 *	����ֵ: �ο��궨��
 */
int VARENDER_API VARender_Snapshot(VARENDER_HANDLE hVARender, const char *pszFileName);

/*  ��������: ץͼ���ڴ�
 *  ����˵��:
 *      char *pBuffer [IN]:	ץ��ͼƬ������ڴ��ַ�����御����㣬���̫С�᷵��VARENDER_E_OVERFLOW
 *		int *piBufferLen [IN,OUT]: �����ʱ����ץ��ͼƬ���ڴ滺�峤�ȣ��������ʵ��ͼƬ���ݵĳ��ȡ�
 *		const char *cpszExt [IN]: ��ʽ��׺��Ŀǰ����֧�֣���jpg"��
 *		int *piWidth [OUT]: ͼƬ�Ŀ�
 *		int *piHeight [OUT]: ͼƬ�ĸߡ�
 *	����ֵ: �ο��궨��
 *	˵��: ����������������ط�ͬʱ���ã������һ��û���أ�����һ���ط����û᷵�أ�VARENDER_E_WOULDBLOCK��
 */
int VARENDER_API VARender_SnapshotMem(VARENDER_HANDLE hVARender, char *pBuffer, int *piBufferLen, const char *cpszExt, int *piWidth, int *piHeight);

/*  ��������: �ػ����һ��ͼ��
 *  ��ע: ����ʾ����ˢ�µ�ʱ������������,�����δ��ʾ����,���˺�������ֺ���
 */
void VARENDER_API VARender_Refresh(VARENDER_HANDLE hVARender);

/*  ��������: ���õ�ǰ��Ƶ�Ƿ�ȷͬ������
 */
void VARENDER_API VARender_SetSync(VARENDER_HANDLE hVARender, int bSync);

/*  ��������: ��ȡ��ǰ��Ƶ�Ƿ�ȷͬ������
 *  ����ֵ: �Ƿ�ȷͬ������
 */
int VARENDER_API VARender_IsSync(VARENDER_HANDLE hVARender);

/*  ��������: ���ò���ģʽ
 *  ����˵��:
 *      int iMode [IN]:		����ģʽ,ȡֵ��ǰ���VARENDER_PLAYMODE_XXX�궨��
 *  ��ע: ʵʱģʽʱ:
 *			1.����ݻ�������ݴ�С����̬���ڲ��ŵ��ٶ�.
 *			2.����Ƶ�Ƿ�ȷͬ������VARender_SetSync��������.Ĭ���ǲ���ȷͬ����.
 *		  �ط�ģʽʱ:
 *			1.�ϸ���ʱ���,����ԭʼ�ٶ�������,��������Ƶ��ȷͬ��.
 *			2.����ͨ��VARender_SetSpeed�����������ı䲥���ٶ�.
 *			3.��ģʽ��ʱ��,�ڲ������֡����Ƚ���,��Ҫ�ϲ㼰ʱ��������
 */
void VARENDER_API VARender_SetPlayMode(VARENDER_HANDLE hVARender, int iMode);

/*  ��������: ��ȡ��ǰ�Ĳ���ģʽ
 *  ����ֵ: ��ǰ�Ĳ���ģʽ
 */
int VARENDER_API VARender_GetPlayMode(VARENDER_HANDLE hVARender);

/*  ��������: ���ò����ٶ�
 *  ����˵��:
 *      int iSpeed [IN]:	�����ٶȵ�ָ��,����Ϊ2,����:
 *								0��ʾ2��0�η�,1����,�����ٶ�
 *								-1��ʾ2��-1�η�,1/2����
 *								1��ʾ2��1�η�,Ϊ2����
 *	��ע: ֻ���ڻط�ģʽʱ��Ч.
 *		  �����ٶȲ��������ٶȵ�ʱ��,���Զ�ֹͣ��Ƶ�Ĳ���.
 */
void VARENDER_API VARender_SetSpeed(VARENDER_HANDLE hVARender, int iSpeed);

/*  ��������: ��ȡ��ǰ�����ٶ�
 *  ����ֵ: ��ǰ�����ٶ�
 */
int VARENDER_API VARender_GetSpeed(VARENDER_HANDLE hVARender);

/*  ��������: ��ȡ/������Ƶ��������,��Χ0-100
 */
int VARENDER_API VARender_GetVolume(VARENDER_HANDLE hVARender);
void VARENDER_API VARender_SetVolume(VARENDER_HANDLE hVARender, int iVolume);

/*  �������������û���ʱ�䣬
 *  ����˵����
 *      int iBufferTime [IN]:		����ʱ�䣬��λ���롣
 *��ע��	���ʱ���������������綶��ʱ�䣬��ʱ�������Զ������š�
 */
void VARENDER_API VARender_SetBufferTime(VARENDER_HANDLE hVARender, int iBufferTime);

//////////////////////////////////////////////////////////////////////////
//	��ȡ����ͳ����Ϣ��
//////////////////////////////////////////////////////////////////////////

/*  ��������: ��ʼ/ֹͣ¼��
 *  ����˵��:
 *      const char *lpszFileName [IN]:		�ļ���(������.aviΪ��׺),��󳤶Ȳ��ɴ���VARENDER_MAXLEN_FILENAME.
 *      unsigned int uiMaxFileTime [IN]:	¼���ļ������ʱ�䳤��,��λ����.�������Ȼ��Զ����ļ�
 *  ����ֵ: ������궨��.
 *	��ע: ���ɵ��ļ����Զ��Ӻ�׺"_00",���ļ���ʱ��,����,"_01","_02",...
 */
int VARENDER_API VARender_StartRecord(VARENDER_HANDLE hVARender, const char *lpszFileName, unsigned int uiMaxFileTime);
void VARENDER_API VARender_CloseRecord(VARENDER_HANDLE hVARender);

/*  ��������: ����¼�񸽼���Ϣ�ļ���Ϣ
 *  ����˵��:
 *      char *pszPUID [IN]:		�豸��PUID
 *      int iResIdx [IN]:		¼����Դ�ı��
 *      char *pszResType [IN]:	¼����Դ������
 *	��ע: ����������������,¼���ʱ��,�ͻ��Ӧ����һ��lfi�ļ�.
 */
void VARENDER_API VARender_SetLfiFileInfo(VARENDER_HANDLE hVARender, char *pszPUID, int iResIdx, char *pszResType);

//////////////////////////////////////////////////////////////////////////
//	��ȡ����ͳ����Ϣ�ĺ���
//////////////////////////////////////////////////////////////////////////

/*  ��������: ��ȡ��ǰ��Ƶ��֡��
 *  ����ֵ: ��ǰ��Ƶ��֡��
 *	��ע:	��һ��������*5/4�İ汾���ڶ���������ʵ��֡�ʡ�
 */
int VARENDER_API VARender_GetFrameRate(VARENDER_HANDLE hVARender);
int VARENDER_API VARender_GetFrameRateReal(VARENDER_HANDLE hVARender);

/*  ��������: ��ȡ��ǰ��Ƶ������
 *  ����ֵ: ��ǰ��Ƶ������
 *	��ע:	��һ��������*4/5�İ汾���ڶ���������ʵ�����ʡ�
 */
int VARENDER_API VARender_GetBitRate(VARENDER_HANDLE hVARender);
int VARENDER_API VARender_GetBitRateReal(VARENDER_HANDLE hVARender);

/*  ��������: ��ȡ������ŵ���Ƶ/��Ƶ֡��ʱ���
 *  ����˵��:
 *      unsigned int *puiTimeStamp [OUT]:	������ŵ�ʱ���
 *  ����ֵ: VARENDER_E_OK			��ʾ�ɹ�
 *			VARENDER_E_INVALID		��û�в���֡
 */
int VARENDER_API VARender_GetLatestPlayVideoTimeStamp(VARENDER_HANDLE hVARender, unsigned int *puiTimeStamp);
int VARENDER_API VARender_GetLatestPlayAudioTimeStamp(VARENDER_HANDLE hVARender, unsigned int *puiTimeStamp);

/*  ��������: ��ȡ��ǰ��Ƶ��Ƶ���������ȵȵ��Բ���
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
