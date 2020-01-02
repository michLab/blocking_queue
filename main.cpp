/**
  @file main.cpp
  @brief An example of usage of BlockingQueue class
  @author Michal Labowski
  @date 02-01-2020
  @version 1.0
 */

#include <iostream>
#include <thread>
#include <gtest/gtest.h>
#include "blockingqueue.h"

using namespace std;

class A {
public:
    int* ptr;
};

//#define RUN_TESTS
int main(int argc, char** argv)
{
#ifndef RUN_TESTS
    /// Create instance of BlockingQueue
    BlockingQueue<std::unique_ptr<A>> q;
    /// Create producer thread:
    //std::thread producer_thread();
    /// Create consumer thread:


    return 0;
#else
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif
}
