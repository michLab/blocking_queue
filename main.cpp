/**
  @file main.cpp
  @brief An example of usage of BlockingQueue class
  @author Michal Labowski
  @date 02-01-2020
  @version 1.0
 */

#include <iostream>
#include <thread>
#include <chrono> /// for sleep_for
#include <gtest/gtest.h>
#include "blockingqueue.h"

using namespace std;

class A {
public:
    int* ptr;
};

void producer(BlockingQueue<std::unique_ptr<A>>& q)
{
    int i = 0;
    while (true) {
        std::unique_ptr<A> a_ptr = std::make_unique<A>();
        a_ptr->ptr[0] = i++;
        std::cout << "[Producer] push data to queue" << std::endl;
        q.push(std::move(a_ptr));
        std::cout << "[Producer] sleeping" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void consumer(BlockingQueue<std::unique_ptr<A>>& q)
{
    int i = 0;
    while (true) {
        std::unique_ptr<A> a_ptr = std::make_unique<A>();
        std::cout << "[Consumer] Waits for data" << std::endl;
        q.pop(a_ptr);
        std::cout << "[Producer] Get data" << std::endl;
        a_ptr.reset();
    }
}

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
