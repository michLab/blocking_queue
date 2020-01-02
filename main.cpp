/**
  @file main.cpp
  @brief An example of usage of UniquePtrQueue class
  @author Michal Labowski
  @date 02-01-2020
  @version 1.0
 */

#include <iostream>
#include <gtest/gtest.h>

using namespace std;

//#define RUN_TESTS
int main(int argc, char** argv)
{
#ifndef RUN_TESTS
    cout << "Hello World!" << endl;
    return 0;
#else
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif
}
