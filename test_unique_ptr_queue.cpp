/**
  @file test_unique_ptr_queue
  @brief Tests for unique_ptr_queue class
  @author Michal Labowski
  @date 02-01-2020
  @version 1.0
 */

#include <memory>
#include <gtest/gtest.h>
#include "blockingqueue.h"


TEST(BlockingQueueTest, size)
{
    BlockingQueue<int> q;
    int data_1 = 1;
    int data_2 = 2;
    q.push(data_1);
    q.push(data_2);

    uint8_t expected_size = 2;
    uint8_t actual_size = static_cast<uint8_t>(q.size());
    EXPECT_EQ(expected_size, actual_size);
}

TEST(BlockingQueueTest, empty_true)
{
    BlockingQueue<int> q;

    bool expected_empty = true;
    bool actual_empty = q.empty();
    EXPECT_EQ(expected_empty, actual_empty);
}

TEST(BlockingQueueTest, empty_false)
{
    BlockingQueue<int> q;
    int data_1 = 1;
    int data_2 = 2;
    q.push(data_1);
    q.push(data_2);

    bool expected_empty = false;
    bool actual_empty = q.empty();
    EXPECT_EQ(expected_empty, actual_empty);
}
