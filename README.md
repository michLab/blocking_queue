# A thread-safe blocking queue template class

This class can be used in single-producer, single-consumer problem, however it could be easly modyfied to
handle multiple-producer, multiple-consumer problem (replace condition_variable.notify_one to condition_variable.notify_all).
The user can define the data type used in queue. The queue supports the copiable and movable (like unique_ptr) data types.

## Usage example

The template class definition is located in single header file: blockingqueue.h. The user has only to
include this file in particular project.

```c++
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

/// Define type used by queue:
typedef A queueItemType;


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


int main(int argc, char** argv)
{
    /// Create instance of BlockingQueue
    BlockingQueue<std::unique_ptr<queueItemType>> q;
    /// Create producer thread
    /// q is passed as reference (not by value):
    std::thread producer_thread(producer, std::ref(q));
    /// Create consumer thread:
    std::thread consumer_thread(consumer, std::ref(q));

    while (true);
}
```

## License
The contents of this repository are covered under the [MIT License](./LICENSE.txt)


## Contributing

1. Fork it
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request
