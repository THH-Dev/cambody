#ifndef __AUDIODECPLAY_H__
#define __AUDIODECPLAY_H__

#define AUDIODECPLAY_VERSION				"v2.0.18.406"	//Library version

//¥ÌŒÛ¬Î∂®“Â
#define AUDIODECPLAY_E_OK					0	//Success
#define AUDIODECPLAY_E_WOULDBLOCK			1	//Operation can not be executed immediately
#define AUDIODECPLAY_E_UNKOWN				-1	//unknown error
#define AUDIODECPLAY_E_MALLOC				-2	//Memory allocation error
#define AUDIODECPLAY_E_UNKOWNFRAMEINFO		-3	//Unsupported frame information
#define AUDIODECPLAY_E_AUDIOPLAYER			-4	//Audio play error
#define AUDIODECPLAY_E_AUDIODEC				-5	//Audio coding error
#define AUDIODECPLAY_E_SEM					-6	//Semaphore error
#define AUDIODECPLAY_E_THREAD				-7	//Thread error

typedef struct _TAudioDecPlay TAudioDecPlay;
typedef TAudioDecPlay* AUDIODECPLAY_HANDLE;

#ifdef WIN32
	#define AUDIODECPLAY_STDCALL __stdcall
	#ifdef AUDIODECPLAY_EXPORTS
		#define AUDIODECPLAY_PORT __declspec(dllexport)
	#else
		#define AUDIODECPLAY_PORT
	#endif
#else
	#define AUDIODECPLAY_STDCALL
	#define AUDIODECPLAY_PORT
#endif
#define AUDIODECPLAY_API AUDIODECPLAY_PORT AUDIODECPLAY_STDCALL

#ifdef __cplusplus
extern "C" {
#endif

/* Function description: Initialize VAReander library
 *   Parameter description:
 *      const char *cpszDLLPath [OUT]:	Path to the external audio and video decoding library, passing NULL means using the embedded decoding library..
 *  Return value: error code, see previous macro definition
 * Note: when the program starts, it must be initialized before other functions can be called, global call once is ok.
 */
int AUDIODECPLAY_API AudioDecPlay_Startup(const char *cpszDLLPath);

/*  Function description: Remove AudioDecPlay library
 *   Note: this function is called before the program exits, otherwise a resource leak may occur
 */
void AUDIODECPLAY_API AudioDecPlay_Cleanup();

/*  Function description: Create AudioDecPlay object
 *  Return value: error code, see previous macro definition
 */
int AUDIODECPLAY_API AudioDecPlay_Open(AUDIODECPLAY_HANDLE *phAudioDecPlay);

/*  Function description: Close AudioDecPlay object
 *  Parameter description:
 *      AUDIODECPLAY_HANDLE hAudioDecPlay [IN]:	AudioDecPlay object handle
 */
void AUDIODECPLAY_API AudioDecPlay_Close(AUDIODECPLAY_HANDLE hAudioDecPlay);

/*  Function description: Insert data frame (starting with the storage frame header)
 * Parameter description:
 *      AUDIODECPLAY_HANDLE hAudioDecPlay [IN]:	AudioDecPlay object handle
 *		char *pFrame [IN]:				Data frame buffer.
 *		int iLen [IN]					Data frame length
 *	Return value: error code, see the macro definition above.
 */
int AUDIODECPLAY_API AudioDecPlay_PumpFrame(AUDIODECPLAY_HANDLE hAudioDecPlay, char *pFrame, int iLen);

/*  Function description: Gets volume of the audio frame
 *  Parameter description:
 *      AUDIODECPLAY_HANDLE hAudioDecPlay [IN]:	AudioDecPlay object handle
 *  Return value: the volume of an audio frame, ranging from 0 to 100.
 */
int AUDIODECPLAY_API AudioDecPlay_GetFrameVolume(AUDIODECPLAY_HANDLE hAudioDecPlay);

#ifdef __cplusplus
}
#endif

#endif //__AUDIODECPLAY_H__
