/*
#if defined(WEBRTC_AECM) || defined(WEBRTC_NSX)

#include "noise_suppression_x.h"
#include "echo_control_mobile.h"
#include "signal_processing_library.h"
#include "hal_trace.h"
#include "ring_buffer.h"

#endif
*/
#if defined(WEBRTC_NSX)
#include "noise_suppression_x.h"
#include "stdio.h"
#include "hal_trace.h"
#endif

#if defined(WEBRTC_AGC)
#include "analog_agc.h"
#endif

#if defined(WEBRTC_AECM)
#include "ring_buffer.h"
#include "echo_control_mobile.h"
//#include "signal_processing_library.h"
#include "hal_trace.h"




void *aecmInst = NULL;
extern int aecm_crt;
extern int aecm_int;
extern int aecm_last;
void WebRtc_aecm_init(int nSample,int nMode)
{
    int ret_val;
    unsigned int count = 1;

	ret_val = WebRtcAecm_Create(&aecmInst);
	TRACE("retVal :%d aecm_crt:%d ",ret_val,aecm_crt);
	ret_val = WebRtcAecm_Init(aecmInst, nSample);
	TRACE("retVal :%d aecm_int:%d ",ret_val,aecm_int);

	AecmConfig config;
	config.cngMode = AecmTrue;
	config.echoMode = nMode;
	ret_val = WebRtcAecm_set_config(aecmInst, config);
	TRACE("retVal :%d aecm_last:%d ",ret_val,aecm_last);

}
#define  NFRAME 80
extern int aecm_cnt;

void WebRtc_aecm_process(short *near_frame, short *out_frame)
{

    int32_t retVal = 0;

    /* 回声消除 8k 采样率 物理延迟是 8ms */
    retVal = WebRtcAecm_Process(aecmInst, near_frame, NULL, out_frame, NFRAME,5);//回声消除

 //   ASSERT(retVal == 0, "WebRtc_aecm_process failed aecm_cnt:%d ",aecm_cnt);
}
#endif

#if defined(WEBRTC_NSX)


pNxsHandle ppNsxHandle = NULL;
void WebRtcNsx_denoise_init(int nSample,int nMode)
{
    int ret_val;
    unsigned int count = 1;

    ret_val = WebRtcNsx_Create(&ppNsxHandle);
    //ASSERT(0 == WebRtcNsx_Create(&ppNsxHandle), "WebRtcNsx_Create failed");

    TRACE("WebRtcNs_denoise_initaaa:%d ",ret_val);

    ret_val = WebRtcNsx_Init(ppNsxHandle,nSample);
    //ASSERT(0 == WebRtcNsx_Init(ppNsxHandle,nSample), "WebRtcNsx_Init failed");

    TRACE("WebRtcNs_denoise_initbbb:%d ",ret_val);

    ret_val = WebRtcNsx_set_policy(ppNsxHandle,nMode);
    //ASSERT(0 == WebRtcNsx_set_policy(ppNsxHandle,nMode), "WebRtcNsx_set_policy failed");

    TRACE("WebRtcNs_denoise_initcccc:%d ",ret_val);

}
void WebRtcNsx_Alg_Process(short *shBufferIn, short *shBufferOut)
{
    int ret_val;

    DEBUG2("WebRtcNs_denoise_initcccc:%d ",ret_val);
    ret_val = WebRtcNsx_Process(ppNsxHandle, shBufferIn, NULL, shBufferOut, NULL);

    //ASSERT(0 == ret_val, "failed in WebRtcNsx_Process :%d ",ret_val);

}

#endif

#if defined(WEBRTC_AGC)
pAgc_t   pAgc = NULL;
void WebRtcAgc_init(void)
{

    WebRtcAgc_Create(&pAgc);
    int minLevel = 0;
    int maxLevel = 255;
    int agcMode  = kAgcModeAdaptiveDigital;
    WebRtcAgc_Init(pAgc, minLevel, maxLevel, agcMode, 8000);

    WebRtcAgc_config_t agcConfig;
    agcConfig.compressionGaindB = 6;
    agcConfig.limiterEnable     = 1;
    agcConfig.targetLevelDbfs   = 9;
    WebRtcAgc_set_config(pAgc, agcConfig);

}

int g_micLevelIn = 0;
int micLevelOut = 0;
#define FRAME_VALUE 80

void WebRtcAgc_Alg_Process(short *pData, short *pOutData)
{

    int inMicLevel  = g_micLevelIn;
    int outMicLevel = 0;
    uint8_t saturationWarning;
    int nAgcRet = WebRtcAgc_Process(pAgc, pData, NULL, FRAME_VALUE, pOutData,NULL, inMicLevel, &outMicLevel, 0, &saturationWarning);

    //ASSERT(0 == nAgcRet, "failed in WebRtcAgc_Process nAgcRet:%d ",nAgcRet);

    g_micLevelIn = outMicLevel;

}

#endif

