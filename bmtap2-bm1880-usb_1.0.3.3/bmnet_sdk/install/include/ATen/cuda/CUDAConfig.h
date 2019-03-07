#pragma once

// Test these using #if AT_CUDNN_ENABLED(), not #ifdef, so that it's
// obvious if you forgot to include Config.h
//    c.f. https://stackoverflow.com/questions/33759787/generating-an-error-if-checked-boolean-macro-is-not-defined

#define AT_CUDNN_ENABLED() 0
#define AT_ROCM_ENABLED() 0
