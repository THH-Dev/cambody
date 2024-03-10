#ifndef __VARECORDER_H__
#define __VARECORDER_H__

#define VARECORDER_VERSION				"v2.0.17.809"	//��İ汾

//�����붨��
#define VARECORDER_E_OK					0	//�ɹ�
#define VARECORDER_E_WOULDBLOCK			1	//�����޷�����ִ��
#define VARECORDER_E_UNKOWN				-1	//δ֪����
#define VARECORDER_E_FRAMEINFOCHANGE	-2	//֡��Ϣ�����ı�
#define VARECORDER_E_UNKOWNFRAMEINFO	-3	//��֧�ֵ�֡��Ϣ
#define VARECORDER_E_MALLOC				-4	//�����ڴ�ʧ��

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

/*  ��������: ��ʼ��VAReander��
 *  ����˵��:
 *      const char *cpszDLLPath [OUT]:	�ⲿ����Ƶ������·��,����NULL��ʾʹ����Ƕ�Ľ����.
 *  ����ֵ: ������,��ǰ��ĺ궨��
 *  ��ע: ����������ʱ������ȳ�ʼ�����ܹ�������������,ȫ�ֵ���һ�μ���.
 */
int VARECORDER_API VARecorder_Startup(const char *cpszDLLPath);

/*  ��������: ���VARender��
 *  ��ע: �����˳�֮ǰ���ô˺���,������������Դй©
 */
void VARECORDER_API VARecorder_Cleanup();

/*  ��������: ����VARecorder����
 *  ����˵��:
 *		const char *lpszFileName [in]: ¼���ļ���
 *      VARECORDER_HANDLE *phVARecorder [OUT]:	�����õ��Ķ�����
 *  ����ֵ: ������,��ǰ��ĺ궨��
 */
int VARECORDER_API VARecorder_Open(const char *lpszFileName, VARECORDER_HANDLE *phVARecorder);

/*  ��������: �ر�VARender����
 *  ����˵��:
 *      VARECORDER_HANDLE hVARecorder [IN]:	VARender������
 */
void VARECORDER_API VARecorder_Close(VARECORDER_HANDLE hVARecorder);

/*  ��������: ���ý�������Ƶ
 *  ����˵��:
 *      VARECORDER_HANDLE hVARecorder [IN]:	VARender������
 */
void VARECORDER_API VARecorder_SetAudioOnly(VARECORDER_HANDLE hVARecorder);

/*  ��������: ������Ƶ���ݣ��Ӵ洢֡ͷ��ʼ��
 *  ����˵��:
 *      VARECORDER_HANDLE hVARecorder [IN]:	VARender������
 *		char *pFrame [IN]:				����֡����.
 *		int iLen [IN]					����֡����
 *	����ֵ,������,��ǰ��ĺ궨��,���ܷ������´�����:
 *			VARECORDER_E_FRAMEINFOCHANGE	֡��Ϣ�����ı�,�ϲ���Ҫ�����ļ�
 *			VARECORDER_E_UNKOWNFRAMEINFO	����ͼ���С,�㷨�Ȳ�֧��
 */
int VARECORDER_API VARecorder_PumpVideoFrame(VARECORDER_HANDLE hVARecorder, char *pFrame, int iLen);

/*  ��������: ���������Ƶ���ݣ��Ӵ洢֡ͷ��ʼ��
 *  ����˵��:
 *      VARECORDER_HANDLE hVARecorder [IN]:	VARender������
 *		char *pFrame [IN]:				����֡����.
 *		int iLen [IN]					����֡����
 *	����ֵ,������,��ǰ��ĺ궨��,���ܷ������´�����:
 *			VARECORDER_E_FRAMEINFOCHANGE	֡��Ϣ�����ı�,�ϲ���Ҫ�����ļ�
 *			VARECORDER_E_UNKOWNFRAMEINFO	������Ƶ�㷨��֧��,���ݳ��Ȳ���ȷ
 */
int VARECORDER_API VARecorder_PumpAudioFrame(VARECORDER_HANDLE hVARecorder, char *pFrame, int iLen);

/*  ��������: ���뺰����Ƶ���ݣ��Ӵ洢֡ͷ��ʼ��
 *  ����˵��:
 *      VARECORDER_HANDLE hVARecorder [IN]:	VARender������
 *		char *pFrame [IN]:				����֡����.
 *		int iLen [IN]					����֡����
 *	����ֵ,������,��ǰ��ĺ궨��,���ܷ������´�����:
 *			VARECORDER_E_FRAMEINFOCHANGE	֡��Ϣ�����ı�,�ϲ���Ҫ�����ļ�
 *			VARECORDER_E_UNKOWNFRAMEINFO	������Ƶ�㷨��֧��,���ݳ��Ȳ���ȷ
 */
int VARECORDER_API VARecorder_PumpCallAudioFrame(VARECORDER_HANDLE hVARecorder, char *pFrame, int iLen);

#ifdef __cplusplus
}
#endif

#endif //__VARECORDER_H__
