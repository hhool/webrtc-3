
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

int micLevelIn = 0;
int micLevelOut = 0;
int frameSize = 80;

void webrtc_agc_process(short *shBufferIn, short *shBufferOut)
{
    int inMicLevel  = micLevelOut;
    int outMicLevel = 0;
    uint8_t saturationWarning;
    int nAgcRet = WebRtcAgc_Process(g_agcHandle, shBufferIn, NULL, frameSize, shBufferOut,NULL, inMicLevel, &outMicLevel, 0, &saturationWarning);
    if (nAgcRet != 0)
    {
    	printf("failed in WebRtcAgc_Process\n");
    	break;
    }
    micLevelIn = outMicLevel;

}


