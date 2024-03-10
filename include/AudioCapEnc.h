//#ifndef __AUDIOCAPENC_H__
//#define __AUDIOCAPENC_H__
//
//#define AUDIOCAPENC_VERSION				"v2.0.17.809"	//Library version
//
////Error code definition
//#define AUDIOCAPENC_E_OK					0	//Success
//#define AUDIOCAPENC_E_UNKOWN				-1	//unknown error
//#define AUDIOCAPENC_E_MALLOC				-2	//Memory allocation error
//#define AUDIOCAPENC_E_OVERFLOW				-3	//Overflow error
//#define AUDIOCAPENC_E_AUDIOCAPTURER			-4	//Audio acquisition error
//#define AUDIOCAPENC_E_AUDIOENC				-5	//Audio coding error
//#define AUDIOCAPENC_E_SEM			                -6	 //Semaphore error
//#define AUDIOCAPENC_E_THREAD				-7	//Thread error
//#define AUDIOCAPENC_E_INITCS				-8	//Creating critical segment segmentprotection object error
//
//typedef struct _TAudioCapEnc TAudioCapEnc;
//typedef TAudioCapEnc * AUDIOCAPENC_HANDLE;
//
//#ifdef WIN32
//	#define AUDIOCAPENC_STDCALL __stdcall
//	#ifdef AUDIOCAPENC_EXPORTS
//		#define AUDIOCAPENC_PORT __declspec(dllexport)
//	#else
//		#define AUDIOCAPENC_POR
//	#endif
//#else
//	#define AUDIOCAPENC_STDCALL
//	#define AUDIOCAPENC_PORT
//#endif
//#define AUDIOCAPENC_API AUDIOCAPENC_PORT AUDIOCAPENC_STDCALL
//
//#ifdef __cplusplus
//extern "C" {
//#endif
//
///*  Function description: get library version
// *  Return value: the version of the library.
// */
//AUDIOCAPENC_PORT const char * AUDIOCAPENC_STDCALL AudioCapEnc_GetVersion();
//
///*  Function description: initialize the AudioCapEnc library
// *  Parameter description:
// *      const char *cpszDLLPath [OUT]:	Path to the external audio and video decoding library, passing NULL means using the embedded decoding library.
// *  Return value: error code, see previous macro definition
// *  Note: when the program starts, it must be initialized before other functions can be called, global call once is ok.
// */
//int AUDIOCAPENC_API AudioCapEnc_Startup(const char *cpszDLLPath);
//
///*  Note: when the program starts, it must be initialized before other functions can be called, global call once.
// *  Note: this function is called before the program exits, otherwise a resource leak may occur
// */
//void AUDIOCAPENC_API AudioCapEnc_Cleanup();
//
///*  Function description: create an AudioCapEnc object
// *  Parameter description:
// *		int iProducerID [IN]£º			Producer ID
// *		const char *cpszAlgName [IN]£º	The name of the audio coding algorithm
// *		unsigned int uiBaseTimeStamp [IN]:	Start timestamp
// *  Return value: error code, see previous macro definition 
// */
//int AUDIOCAPENC_API AudioCapEnc_Open(int iProducerID, const char *cpszAlgName, unsigned int uiBaseTimeStamp, AUDIOCAPENC_HANDLE *phAudioCapEnc);
//
///*  Function description: close the AudioCapEnc object
// *  Parameter description:
// *      AUDIOCAPENC_HANDLE hAudioCapEnc [IN]:	Handle to the AudioCapEnc object
// */
//void AUDIOCAPENC_API AudioCapEnc_Close(AUDIOCAPENC_HANDLE hAudioCapEnc);
//
///*  Function description: read data frame (including storage frame header)
// *  Parameter description:
// *      AUDIOCAPENC_HANDLE hAudioCapEnc [IN]:	Handle to the AudioCapEnc object
// *		char *pFrame [IN]:				Data frame buffer.
// *		int iLen [IN]					Data frame length
// *  Return value: length of the encoded audio frame, less than 0 indicates error, 0 indicates no data.
// */
//int AUDIOCAPENC_API AudioCapEnc_ReadFrame(AUDIOCAPENC_HANDLE hAudioCapEnc, char *pFrame, int iLen);
//
///*  Function description: Gets the volume of the audio frame
// *  Parameter description:
// *      AUDIOCAPENC_HANDLE hAudioCapEnc [IN]:	Handle to the AudioCapEnc object
// *  Return value: the volume of audio frame, ranging from 0 to 100.
// */
//int AUDIOCAPENC_API AudioCapEnc_GetFrameVolume(AUDIOCAPENC_HANDLE hAudioCapEnc);
//
//#ifdef __cplusplus
//}
//#endif
//
//#endif //__AUDIOCAPENC_H__
#ifndef __AUDIOCAPENC_H__
#define __AUDIOCAPENC_H__

#define AUDIOCAPENC_VERSION             "v2.0.17.809"    // Library version

// Error code definition
#define AUDIOCAPENC_E_OK                0    // Success
#define AUDIOCAPENC_E_UNKOWN            -1   // Unknown error
#define AUDIOCAPENC_E_MALLOC            -2   // Memory allocation error
#define AUDIOCAPENC_E_OVERFLOW          -3   // Overflow error
#define AUDIOCAPENC_E_AUDIOCAPTURER     -4   // Audio acquisition error
#define AUDIOCAPENC_E_AUDIOENC          -5   // Audio coding error
#define AUDIOCAPENC_E_SEM               -6   // Semaphore error
#define AUDIOCAPENC_E_THREAD            -7   // Thread error
#define AUDIOCAPENC_E_INITCS            -8   // Creating critical segment segment protection object error

typedef struct _TAudioCapEnc TAudioCapEnc;
typedef TAudioCapEnc* AUDIOCAPENC_HANDLE;

#ifdef WIN32
#define AUDIOCAPENC_STDCALL __stdcall
#ifdef AUDIOCAPENC_EXPORTS
#define AUDIOCAPENC_PORT __declspec(dllexport)
#else
#define AUDIOCAPENC_PORT
#endif
#else
#define AUDIOCAPENC_STDCALL
#define AUDIOCAPENC_PORT
#endif
#define AUDIOCAPENC_API AUDIOCAPENC_PORT AUDIOCAPENC_STDCALL

#ifdef __cplusplus
extern "C" {
#endif

	/*  Function description: get library version
	 *  Return value: the version of the library.
	 */
	AUDIOCAPENC_PORT const char* AUDIOCAPENC_STDCALL AudioCapEnc_GetVersion();

	/*  Function description: initialize the AudioCapEnc library
	 *  Parameter description:
	 *      const char *cpszDLLPath [OUT]:    Path to the external audio and video decoding library, passing NULL means using the embedded decoding library.
	 *  Return value: error code, see previous macro definition
	 *  Note: when the program starts, it must be initialized before other functions can be called, global call once is ok.
	 */
	int AUDIOCAPENC_API AudioCapEnc_Startup(const char* cpszDLLPath);

	/*  Note: when the program starts, it must be initialized before other functions can be called, global call once.
	 *  Note: this function is called before the program exits, otherwise a resource leak may occur
	 */
	void AUDIOCAPENC_API AudioCapEnc_Cleanup();

	/*  Function description: create an AudioCapEnc object
	 *  Parameter description:
	 *      int iProducerID [IN]£º             Producer ID
	 *      const char *cpszAlgName [IN]£º     The name of the audio coding algorithm
	 *      unsigned int uiBaseTimeStamp [IN]: Start timestamp
	 *  Return value: error code, see previous macro definition
	 */
	int AUDIOCAPENC_API AudioCapEnc_Open(int iProducerID, const char* cpszAlgName, unsigned int uiBaseTimeStamp, AUDIOCAPENC_HANDLE* phAudioCapEnc);

	/*  Function description: close the AudioCapEnc object
	 *  Parameter description:
	 *      AUDIOCAPENC_HANDLE hAudioCapEnc [IN]:    Handle to the AudioCapEnc object
	 */
	void AUDIOCAPENC_API AudioCapEnc_Close(AUDIOCAPENC_HANDLE hAudioCapEnc);

	/*  Function description: read data frame (including storage frame header)
	 *  Parameter description:
	 *      AUDIOCAPENC_HANDLE hAudioCapEnc [IN]:    Handle to the AudioCapEnc object
	 *      char *pFrame [IN]:                        Data frame buffer.
	 *      int iLen [IN]                            Data frame length
	 *  Return value: length of the encoded audio frame, less than 0 indicates error, 0 indicates no data.
	 */
	int AUDIOCAPENC_API AudioCapEnc_ReadFrame(AUDIOCAPENC_HANDLE hAudioCapEnc, char* pFrame, int iLen);

	/*  Function description: Gets the volume of the audio frame
	 *  Parameter description:
	 *      AUDIOCAPENC_HANDLE hAudioCapEnc [IN]:    Handle to the AudioCapEnc object
	 *  Return value: the volume of audio frame, ranging from 0 to 100.
	 */
	int AUDIOCAPENC_API AudioCapEnc_GetFrameVolume(AUDIOCAPENC_HANDLE hAudioCapEnc);

#ifdef __cplusplus
}
#endif

#endif //__AUDIOCAPENC_H__