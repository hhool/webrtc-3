/*
 *  Copyright (c) 2011 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */


/*
 * This header file contains some internal resampling functions.
 *
 */

#ifndef WEBRTC_RESAMPLE
#define WEBRTC_RESAMPLE

#include "typedefs.h"

/*******************************************************************
 * resample.c
 * Functions for internal use in the other resample functions
 ******************************************************************/
 void WebRtcSpl_Resample48khzTo16khz(const int16_t* in, int16_t* out,
                                    WebRtcSpl_State48khzTo16khz* state, int32_t* tmpmem);
void WebRtcSpl_Resample16khzTo48khz(const int16_t* in, int16_t* out,
                                    WebRtcSpl_State16khzTo48khz* state, int32_t* tmpmem);
#endif // WEBRTC_RESAMPLE
