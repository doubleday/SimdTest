//
//  TestController.h
//  SimdTest
//
//  Created by Daniel Doubleday on 05/07/15.
//  Copyright (c) 2015 Daniel Doubleday. All rights reserved.
//

#ifndef SimdTest_TestController_h
#define SimdTest_TestController_h

#include <array>
#include <chrono>
#include "TestRunner.hpp"
#include "SequentialOps.hpp"
#include "NovaSimdOps.hpp"
#include "VDSPLibOps.hpp"
#include "SimdppOps.hpp"

typedef enum OpsImplementer {
    Sequential,
    NovaSimd,
    VDSPLib,
    Simdpp,
} OpsImplementer;

template <OpsImplementer implementer>
struct ImplementerTrait
{
    using Implenter = SequentialOps;
};

template <>
struct ImplementerTrait<NovaSimd>
{
    using Implenter = NovaSimdOps;
};

template <>
struct ImplementerTrait<VDSPLib>
{
    using Implenter = VDSPLibOps;
};

template <>
struct ImplementerTrait<Simdpp>
{
    using Implenter = SimdppOps;
};

class TestController
{
public:
    TestController() : _blockSize(8), _numTestRuns(100000)
    {
        initBuffers();
    }
    
    template <OpsImplementer implementer>
    double runTestAdd1()
    {
        using namespace std::chrono;
        using Implementer = typename ImplementerTrait<implementer>::Implenter;
        
        auto start = high_resolution_clock::now();
        TestRunner<Implementer>::addTest1(_buffers[0], _buffers[1], _buffers[2], _blockSize, _numTestRuns);
        
        return (double) duration_cast<nanoseconds>(high_resolution_clock::now() - start).count() /
                        duration_cast<nanoseconds>(milliseconds(1)).count();
    }

private:

    void initBuffers()
    {
        for (auto& buffer : _buffers)
        {
            posix_memalign((void**)&buffer, 4 * sizeof(float), _blockSize * sizeof(float));
        }
    }
    
private:
    unsigned int _numTestRuns;
    size_t _blockSize;
    std::array<float*, 3> _buffers;
    
};


#endif
