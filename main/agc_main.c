/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2015年12月03日 16时29分36秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//#include "webrtc_test.h"
//#include "webrtc_main.h"
#include "nsx_main.h"
#include "resample.h"
#include "signal_processing_library.h"
#include "spl_inl.h"

#ifdef WEBRTC_AGC
#endif
#define MAXSTRLEN 1024

void* state1_;
void* state2_;
void* state3_;

extern void test_func_web(void);

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf(stderr, "Usage: <in> <out>\n");
        return -1;
    }
	char *fileIn  = argv[1];
	char *fileOut = argv[2];
    //ZeusFront front;
    int status;

   clock_t start, finish;
   double  duration;
   int count;
  //  status = front.FrontInit(16000, 16, 6, 3, 3);
  //  test_func_web();
    WebRtcNsx_denoise_init(16000,2);
    
    FILE *inFp  = fopen(fileIn,"r");
    FILE *outFp = fopen(fileOut,"w");
    if(inFp == NULL || outFp == NULL)
    {
        fprintf(stderr, "failed to open pcm\n");
        return -1;
    }

#ifdef RESAMPLER
    int tempSize_48k = 768,tmp_buff_size = 496,tmp_buff_out_size = 336;
    short *in_48k  = (short*)calloc(tempSize_48k, sizeof(short));
    short *out_48k = (short*)calloc(tempSize_48k, sizeof(short));
    int32_t *tmp_buff = (int32_t*)calloc(tmp_buff_size, sizeof(int32_t));
   // int32_t *tmp_buff_out = (int32_t*)calloc(tmp_buff_out_size, sizeof(int32_t));
    int32_t *tmp_mem_out = (int32_t*)(malloc(336 * sizeof(int32_t)));
    state2_ = malloc(sizeof(WebRtcSpl_State48khzTo16khz));
    state3_ = malloc(sizeof(WebRtcSpl_State16khzTo48khz));
    int pcmLen = tempSize_48k;
#endif

    int tempSize_16k = 160;
    short *in_16k  = (short*)calloc(tempSize_16k, sizeof(short));
    short *out_16k = (short*)calloc(tempSize_16k, sizeof(short));
   // int pcmLen = tempSize;
    
    start = clock();

    while(pcmLen > 0)
    {
        pcmLen = fread(in_48k, sizeof(short), tempSize_48k, inFp);
  	WebRtcSpl_Resample48khzTo16khz(in_48k,in_16k,(WebRtcSpl_State48khzTo16khz*)state2_,tmp_buff);
 //      	WebRtcNsx_Alg_Process(in_16k,out_16k);
#if 1
	WebRtcSpl_Resample16khzTo48khz(out_16k,out_48k,(WebRtcSpl_State16khzTo48khz*)state3_,tmp_mem_out);
        pcmLen = fwrite(out_48k, sizeof(short), pcmLen, outFp);
#else
        fwrite(out_16k, sizeof(short), pcmLen/3, outFp);
#endif
	count++;
    }

 //   test_func_web();
    //test_aaa(1000);

    finish = clock();
    printf("count:%d speed time:%f \n",count,(double)(finish - start) / CLOCKS_PER_SEC);

    fclose(inFp);
    fclose(outFp);
    free(in_16k);
    free(out_16k);
#ifdef RESAMPLER
    free(state2_);
    free(state3_);
    free(tmp_buff);
    free(tmp_mem_out);
    free(out_48k);
    free(in_48k);
#endif
    return 0;
}
