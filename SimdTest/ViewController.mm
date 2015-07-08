//
//  ViewController.m
//  SimdTest
//
//  Created by Daniel Doubleday on 05/07/15.
//  Copyright (c) 2015 Daniel Doubleday. All rights reserved.
//

#import "ViewController.h"
#import "TestController.hpp"

@interface ViewController ()
@property TestController* testController;
@end

@implementation ViewController

- (id)init
{
    if (self = [super init])
    {
        self.testController = new TestController();
    }
    return self;
}

- (void)dealloc
{
    delete self.testController;
}

// create objc++ methods for the test to prevent inlining
// makes asm analysis easier ...

#define TEST_METHOD(TEST_NAME, IMPL)                 \
- (double)TEST_NAME ## IMPL                          \
{                                                    \
    return self.testController->TEST_NAME<IMPL>();   \
}

TEST_METHOD(runTestAdd1, Sequential)
TEST_METHOD(runTestAdd1, NovaSimd)
TEST_METHOD(runTestAdd1, VDSPLib)
TEST_METHOD(runTestAdd1, Simdpp)

- (IBAction)startTestOnTouchUpInside:(id)sender {

    TestController testController;
    
    NSMutableString *buffer = [NSMutableString string];
    
    double execTime;
    
    execTime = [self runTestAdd1Sequential];
    [buffer appendFormat:@"sequential %f\n", execTime];
    
    execTime = [self runTestAdd1NovaSimd];
    [buffer appendFormat:@"simd %f\n", execTime];
    
    execTime = [self runTestAdd1VDSPLib];
    [buffer appendFormat:@"vdsp %f\n", execTime];

    execTime = [self runTestAdd1Simdpp];
    [buffer appendFormat:@"simdpp %f\n", execTime];

    [self.debugOutput setText:buffer];
    
}

@end
