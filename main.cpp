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

/// Define classes used during testing:
class A {
public:
    A() {
        data = nullptr;
    }
    int* data;
};

class B {
public:
    B() {
        data = 1;
    }
    int data;
};


/// Define type used by queue:
typedef A queueItemType;

/**
  @brief A producer callback
  @param q A reference to BlockingQueue object. Here q is a reference to temporary
  object q qreated on thread stack
  */
[[noreturn]] void producer(BlockingQueue<std::unique_ptr<queueItemType>>& q)
{
    int i = 0;
    while (true) {
        std::unique_ptr<queueItemType> a_ptr = std::make_unique<queueItemType>();
        a_ptr->data = new int;
        a_ptr->data[0] = i++;
        std::cout << "[Producer] push data to queue" << std::endl;
        q.push(std::move(a_ptr));
        std::cout << "[Producer] sleeping" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

/**
  @brief A consumer callback
  @param q A reference to BlockingQueue object
  */
[[noreturn]] void consumer(BlockingQueue<std::unique_ptr<queueItemType>>& q)
{
    while (true) {
        std::unique_ptr<queueItemType> a_ptr = std::make_unique<queueItemType>();
        std::cout << "[Consumer] Waits for data" << std::endl;
        q.pop(a_ptr);
        std::cout << "[Consumer] Get data" << std::endl;
        a_ptr.reset(); /// Destroy object currently menaged by unique_ptr
    }
}

/**
  @brief The main function
  @param argc Argument count
  @param argv Argument table
  */
//#define RUN_TESTS
int main(int argc, char** argv)
{
#ifndef RUN_TESTS
    /// Create instance of BlockingQueue
    BlockingQueue<std::unique_ptr<queueItemType>> q;
    /// Create producer thread
    /// q is passed as reference (not by value):
    std::thread producer_thread(producer, std::ref(q));
    /// Create consumer thread:
    std::thread consumer_thread(consumer, std::ref(q));

    while (true);
#else
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif
}
