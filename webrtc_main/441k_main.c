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
//#include "resample.h"
#include "signal_processing_library.h"
#include "spl_inl.h"

#define MAXSTRLEN 1024

void* state1_;
void* state2_;
void* state3_;
void* state4_;

extern void test_func_web(void);

//static int32_t array_i22k_buff[104];//in_22k_size, sizeof(int32_t)
//static int32_t array_o22k_buff[88];//in_22k_size, sizeof(int32_t)

void WebRtcNsx_44k_denoise(short *i44k_buff, short *o44k_buff)
{
    short array_22k[220]; //tempSize_22k*sizeof(short)
    short array_i16k[160]; //tempSize_22k*sizeof(short)
    short array_o16k[160]; //tempSize_22k*sizeof(short)
    int tempSize_44k = 440;

    int32_t array_i22k_buff[104];//in_22k_size, sizeof(int32_t)
    int32_t array_o22k_buff[88];//in_22k_size, sizeof(int32_t)

    WebRtcSpl_DownsampleBy2(i44k_buff, tempSize_44k, array_22k,(int32_t*)state1_);
    WebRtcSpl_Resample22khzTo16khz(array_22k,array_i16k,(WebRtcSpl_State22khzTo16khz*)state3_,array_i22k_buff);

    WebRtcNsx_Alg_Process(array_i16k,array_o16k);

    WebRtcSpl_Resample16khzTo22khz(array_o16k,array_22k,(WebRtcSpl_State16khzTo22khz*)state4_,array_o22k_buff);
    WebRtcSpl_UpsampleBy2(array_22k, tempSize_44k/2, o44k_buff,(int32_t*)(state2_));
}

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
    int tempSize_22k = 220, in_22k_size = 104, out_22k_size = 88;
    int tempSize_44k = 440;

    short *in_22k  = (short*)calloc(tempSize_22k, sizeof(short));
    short *out_22k = (short*)calloc(tempSize_22k, sizeof(short));
    short *in_44k  = (short*)calloc(tempSize_44k, sizeof(short));
    short *out_44k = (short*)calloc(tempSize_44k, sizeof(short));
    int32_t *tmp_buff = (int32_t*)calloc(in_22k_size, sizeof(int32_t));
   // int32_t *tmp_buff_out = (int32_t*)calloc(tmp_buff_out_size, sizeof(int32_t));
    int32_t *tmp_mem_out = (int32_t*)(malloc(out_22k_size * sizeof(int32_t)));
    state3_ = malloc(sizeof(WebRtcSpl_State22khzTo16khz));
    state4_ = malloc(sizeof(WebRtcSpl_State16khzTo22khz));
    state1_ = malloc(8 * sizeof(int32_t));
    memset(state1_, 0, 8 * sizeof(int32_t));
    state2_ = malloc(8 * sizeof(int32_t));
    memset(state2_, 0, 8 * sizeof(int32_t));
    int pcmLen = tempSize_44k;
#endif

    int tempSize_16k = 160;
    short *in_16k  = (short*)calloc(tempSize_16k, sizeof(short));
    short *out_16k = (short*)calloc(tempSize_16k, sizeof(short));
   // int pcmLen = tempSize;

    start = clock();

    while(pcmLen > 0)
    {
        pcmLen = fread(in_44k, sizeof(short), tempSize_44k, inFp);
        #if 0
	//merge_two_track_to_one_track_16bits(0,in_44k,in_22k,pcmLen);
      	WebRtcSpl_DownsampleBy2(in_44k, tempSize_44k, in_22k,(int32_t*)state1_);
	WebRtcSpl_Resample22khzTo16khz(in_22k,in_16k,(WebRtcSpl_State22khzTo16khz*)state3_,tmp_buff);
       	WebRtcNsx_Alg_Process(in_16k,out_16k);
#if 1
	WebRtcSpl_Resample16khzTo22khz(out_16k,out_22k,(WebRtcSpl_State16khzTo22khz*)state4_,tmp_mem_out);
	WebRtcSpl_UpsampleBy2(out_22k, pcmLen/2, out_44k,(int32_t*)(state2_));
        pcmLen = fwrite(out_44k, sizeof(short), pcmLen, outFp);
#else
        fwrite(out_16k, sizeof(short),(pcmLen/11)*4, outFp);
#endif
        #else
        WebRtcNsx_44k_denoise(in_44k,out_44k);
        pcmLen = fwrite(out_44k, sizeof(short), pcmLen, outFp);
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
    free(state1_);
   // free(state2_);
    free(state3_);
    free(state4_);
    free(tmp_buff);
    free(tmp_mem_out);
    free(out_44k);
    free(in_44k);
    free(out_22k);
    free(in_22k);
#endif
    return 0;
}
