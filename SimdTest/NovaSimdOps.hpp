//
//  NovaSimdOps.h
//  SimdTest
//
//  Created by Daniel Doubleday on 06/07/15.
//  Copyright (c) 2015 Daniel Doubleday. All rights reserved.
//

#ifndef SimdTest_NovaSimdOps_h
#define SimdTest_NovaSimdOps_h

#include <nova/vec.hpp>

using namespace nova;

class NovaSimdOps
{

public:
    
    static void add(float* dest, const float* src1, const float* src2, size_t count)
    {
        vec<float> destVec, src1Vec, src2Vec;
        
        for (int i = 0; i < count; i += 4)
        {
            src1Vec.load_aligned(src1 + i);
            src2Vec.load_aligned(src2 + i);
            destVec = src1Vec + src2Vec;
            destVec.store_aligned(dest + i);
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
