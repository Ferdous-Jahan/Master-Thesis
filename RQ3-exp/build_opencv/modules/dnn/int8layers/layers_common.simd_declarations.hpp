#define CV_CPU_SIMD_FILENAME "/Users/ferdousjahan/Documents/MyStuffs/Thesis/Master-Thesis/RQ3-exp/opencv/modules/dnn/src/int8layers/layers_common.simd.hpp"
#define CV_CPU_DISPATCH_MODE AVX2
#include "opencv2/core/private/cv_cpu_include_simd_declarations.hpp"

#define CV_CPU_DISPATCH_MODE AVX512_SKX
#include "opencv2/core/private/cv_cpu_include_simd_declarations.hpp"

#define CV_CPU_DISPATCH_MODE RVV
#include "opencv2/core/private/cv_cpu_include_simd_declarations.hpp"

#define CV_CPU_DISPATCH_MODE LASX
#include "opencv2/core/private/cv_cpu_include_simd_declarations.hpp"

#define CV_CPU_DISPATCH_MODES_ALL LASX, RVV, AVX512_SKX, AVX2, BASELINE

#undef CV_CPU_SIMD_FILENAME
