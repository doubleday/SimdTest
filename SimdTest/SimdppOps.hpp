//
//  SimdppOps.hpp
//  SimdTest
//
//  Created by Daniel Doubleday on 07/07/15.
//  Copyright (c) 2015 Daniel Doubleday. All rights reserved.
//

#ifndef SimdTest_SimdppOps_hpp
#define SimdTest_SimdppOps_hpp

#include <simdpp/simd.h>

using namespace simdpp;
using namespace simdpp::SIMDPP_ARCH_NAMESPACE;

class SimdppOps
{
    
public:
    
    static void add(float* dest, const float* src1, const float* src2, size_t count)
    {
        float32x4 src1Vec, src2Vec;
        for (int i = 0; i < count; i += 4)
        {
            load(src1Vec, src1 + i);
            load(src2Vec, src1 + i);
            simdpp::store(dest + i, simdpp::add(src1Vec, src2Vec));
        }
    }
    
    static void fill(float* dest, float value, size_t count)
    {
        for (auto i = 0; i < count; ++i) {
            dest[i] = value;
        }
    }
    
};

#endif
