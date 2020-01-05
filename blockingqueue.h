/**
  @file blockingqueue.h
  @brief A declaration of BlockingQueue class
  @author Michal Labowski
  @date 02-01-2020
  @version 1.2
 */

#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class BlockingQueue
{
public:

    /**
     * @brief BlockingQueue a default constructor
     */
    BlockingQueue()
    {
    }
    /**
     * @brief A pop method for copyable/assingnable data types
     * @return A reference to the oldest queue element
     */
    T pop()
    {
        /// We use conditional variable to synchronize access to queue
        /// then we have to use unique_lock instead of lock_guard.
        /// Lock the mutex:
        std::unique_lock<std::mutex> mlock(mutex_);
        while (queue_.empty()) {
            /// wait() function unlock the mutex and waits for notification
            /// (thread is blocked). Then wait(..) reacquires the lock and proceeds.
            cond_var_.wait(mlock);
            /// After notification we perform extra check of empty condition
            /// of queue to avoid spurious wakes (we assume that we could be
            /// wrongly notified while the queue is still empty).
        }
        /// Get a reference to the queue's element:
        auto item = queue_.front();
        /// Remove element from the list (calls the element's destructor):
        queue_.pop();
        return item;
    }

    /**
     * @brief Pop element from queue (can be used with all data types - also movable
     * like unique_ptr)
     * @param item A reference to T-type object
     */
    void pop(T &item)
    {
        /// We use conditional variable to synchronize access to queue
        /// then we have to use unique_lock instead of lock_guard.
        /// Lock the mutex:
        std::unique_lock<std::mutex> mlock(mutex_);
        while (queue_.empty()) {
            /// wait() function unlock the mutex and waits for notification
            /// (thread is blocked). Then wait(..) reacquires the lock and proceeds.
            cond_var_.wait(mlock);
            /// After notification we perform extra check of empty condition
            /// of queue to avoid spurious wakes (we assume that we could be
            /// wrongly notified while the queue is still empty).
        }
        /// Move element data to the item (the queue element may be empty afterwards).
        /// The move semantics is important for unique_ptr elements
        item = std::move(queue_.front());
        /// Remove element from the list (calls the element's destructor):
        queue_.pop();
    }

    /**
     * @brief Push element passed by reference to the queue.
     * Used with copyable nad assignable data types.
     * @param a const reference to the T-type object
     */
    void push(const T &item)
    {
        /// We use conditional variable to synchronize access to queue
        /// then we have to use unique_lock instead of lock_guard.
        /// Lock the mutex:
        std::unique_lock<std::mutex> mlock(mutex_);
        queue_.push(item);
        mlock.unlock();
        cond_var_.notify_one();
    }

    /**
     * @brief Push element passed by rvalue reference to the queue.
     * Used with moveable data types.
     * @param a rvalue reference to the T-type object
     */
    void push(T &&item)
    {
        /// We use conditional variable to synchronize access to queue
        /// then we have to use unique_lock instead of lock_guard.
        /// Lock the mutex:
        std::unique_lock<std::mutex> mlock(mutex_);
        queue_.push(std::move(item));
        mlock.unlock();
        cond_var_.notify_one();
    }

    /**
     * @brief Get queue size
     * @return Number of elements in the queue
     */
    size_t size()
    {
       std::unique_lock<std::mutex> mlock(mutex_);
       return queue_.size();
    }

    /**
     * @brief Get queue empty flag
     * @return True whether queue is empty (whether size is zero)
     */
    bool empty()
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        return queue_.empty();
    }

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_var_;

};

#endif // BLOCKINGQUEUE_H
