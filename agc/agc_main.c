
#include "gain.control.h"

void *g_agcHandle = NULL;


void webrtc_agc_init()
{
    	WebRtcAgc_Create(&g_agcHandle);

		int minLevel = 0;
		int maxLevel = 255;
		int agcMode  = kAgcModeFixedDigital;
		WebRtcAgc_Init(g_agcHandle, minLevel, maxLevel, agcMode, fs);

		WebRtcAgc_config_t agcConfig;
		agcConfig.compressionGaindB = 31;
		agcConfig.limiterEnable     = 1;
		agcConfig.targetLevelDbfs   = 6;
		WebRtcAgc_set_config(g_agcHandle, agcConfig);
}
void WebRtcNsx_denoise_init(int nSample,int nMode)
{
    int ret_val;
    unsigned int count = 1;

    ret_val = WebRtcNsx_Create(&ppNsxHandle);
    //ASSERT(0 == WebRtcNsx_Create(&ppNsxHandle), "WebRtcNsx_Create failed");

 //   TRACE("WebRtcNs_denoise_initaaa:%d ",ret_val);

    ret_val = WebRtcNsx_Init(ppNsxHandle,nSample);
    //ASSERT(0 == WebRtcNsx_Init(ppNsxHandle,nSample), "WebRtcNsx_Init failed");

 //   TRACE("WebRtcNs_denoise_initbbb:%d ",ret_val);

    ret_val = WebRtcNsx_set_policy(ppNsxHandle,nMode);
    //ASSERT(0 == WebRtcNsx_set_policy(ppNsxHandle,nMode), "WebRtcNsx_set_policy failed");

    TRACE("WebRtcNs_denoise_initcccc:%d \n",ret_val);

}

void WebRtcNsx_Alg_Process(short *shBufferIn, short *shBufferOut)
{
    int ret_val;

  //  DEBUG2("WebRtcNs_denoise_initcccc:%d ",ret_val);
    ret_val = WebRtcNsx_Process(ppNsxHandle, shBufferIn, NULL, shBufferOut, NULL);

    //ASSERT(0 == ret_val, "failed in WebRtcNsx_Process :%d ",ret_val);

}


