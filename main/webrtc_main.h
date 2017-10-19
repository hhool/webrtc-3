#include <stddef.h>

#include "typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif
#define  NFRAME 80


#if defined(WEBRTC_AECM)
void WebRtc_aecm_init(int nSample,int nMode);
void WebRtc_aecm_process(short *near_frame, short *out_frame);

extern void *aecmInst;
#endif

//#if defined(WEBRTC_NSX)
void WebRtcNsx_denoise_init(int nSample,int nMode);
void WebRtcNsx_Alg_Process(short *shBufferIn, short *shBufferOut);
//#endif

#if defined(WEBRTC_AGC)
void WebRtcAgc_init(void);
void WebRtcAgc_Alg_Process(short *pData, short *pOutData);
#endif
#ifdef __cplusplus
}
#endif

