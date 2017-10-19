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

#define MAXSTRLEN 1024

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
    int tempSize = 160;
    short *in  = (short*)calloc(tempSize, sizeof(short));
    short *out = (short*)calloc(tempSize, sizeof(short));
    int pcmLen = tempSize;
    
    start = clock();

    while(pcmLen > 0)
    {
        pcmLen = fread(in, sizeof(short), tempSize, inFp);
	WebRtcNsx_Alg_Process(in,out);
        pcmLen = fwrite(out, sizeof(short), pcmLen, outFp);
	count++;
    }

 //   test_func_web();
    //test_aaa(1000);

    finish = clock();
    printf("count:%d speed time:%f \n",count,(double)(finish - start) / CLOCKS_PER_SEC);

    fclose(inFp);
    fclose(outFp);
    free(in);
    free(out);
    return 0;
}
