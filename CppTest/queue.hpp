#ifndef queue_hpp
#define queue_hpp

#include <iostream>
#include <vector>
#include <optional>

using namespace std;

template <typename T>
class Queue
{
public:
    Queue() {}

    void queue(T item)
    {
        list.push_back(item);
    }

    void deque()
    {
        if (list.empty())
            return;

        auto it = list.begin();
        list.erase(it);
    }

    void printQueue()
    {
        for (auto element : list)
        {
            cout << element << " ";
        }
        cout << endl;
    }

private:
    vector<T> list;
};

namespace queue
{
    void test()
    {
        Queue<int> q;
        q.queue(1);
        q.queue(2);

        q.printQueue();

        q.deque();

        q.printQueue();
    }
}

#endif