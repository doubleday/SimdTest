//
//  SequentialOps.h
//  SimdTest
//
//  Created by Daniel Doubleday on 05/07/15.
//  Copyright (c) 2015 Daniel Doubleday. All rights reserved.
//

#ifndef SimdTest_SequentialOps_h
#define SimdTest_SequentialOps_h

class SequentialOps
{
public:
    
    static void add(float* dest, const float* src1, const float* src2, size_t count)
    {
        for (auto i = 0; i < count; ++i) {
            dest[i] = src1[i] + src2[i];
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
