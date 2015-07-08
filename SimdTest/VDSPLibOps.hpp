//
//  VecLibOps.hpp
//  SimdTest
//
//  Created by Daniel Doubleday on 06/07/15.
//  Copyright (c) 2015 Daniel Doubleday. All rights reserved.
//

#ifndef SimdTest_VecLibOps_hpp
#define SimdTest_VecLibOps_hpp

#include <Accelerate/Accelerate.h>

class VDSPLibOps
{
public:
    
    static void add(float* dest, const float* src1, const float* src2, size_t count)
    {
        vDSP_vadd(src1, 1, src2, 1, dest, 1, count);
    }
    
    static void fill(float* dest, float value, size_t count)
    {
        for (auto i = 0; i < count; ++i) {
            dest[i] = value;
        }
    }
};


#endif
