#include "webrtc_main.h"
#include "noise_suppression_x.h"
#include "stdio.h"
#include "hal_trace.h"

void test_aaa(int count)
{
	count = 1000;
}

pNxsHandle ppNsxHandle = NULL;
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

void test_func_web(void)
{
	
	int i = 0;
//	WebRtcNsx_denoise_init(16000,1);
 //   TRACE(" test_func_web");
}

