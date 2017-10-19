#include <stddef.h>

#include "typedefs.h"

#ifdef __cplusplus
extern "C" {
#endif

void webrtc_agc_init();

void webrtc_agc_process(short *shBufferIn, short *shBufferOut);

#ifdef __cplusplus
}
#endif

