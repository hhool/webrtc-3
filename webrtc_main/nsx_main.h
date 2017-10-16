#include <stddef.h>

#include "typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

void test_aaa(int count);
void WebRtcNsx_denoise_init(int nSample,int nMode);
void WebRtcNsx_Alg_Process(short *shBufferIn, short *shBufferOut);
void test_func_web(void);

#ifdef __cplusplus
}
#endif

