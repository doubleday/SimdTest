//
//  TestRunner.hpp
//  SimdTest
//
//  Created by Daniel Doubleday on 07/07/15.
//  Copyright (c) 2015 Daniel Doubleday. All rights reserved.
//

#ifndef SimdTest_TestRunner_hpp
#define SimdTest_TestRunner_hpp

template <typename Ops>
class TestRunner
{
public:
    
    static void addTest1(float* dest, const float* src1, const float* src2, size_t count, int numTestRuns)
    {
        for (int i = 0; i < numTestRuns; ++i)
        {
            Ops::add(dest, src1, src2, count);
        }
    }
};

#endif
