#ifndef stack_hpp
#define stack_hpp

#include <iostream>
#include <vector>
#include <optional>

using namespace std;

template <typename T>
class Stack
{
public:
    int maxSize;

    Stack(int maxSize)
    {
        this->maxSize = maxSize;
    }

    optional<T> peek()
    {
        if (isEmtpy())
        {
            cout << "Can't peek . Stack is empty." << endl;
            return nullopt;
        }

        return list.back();
    }

    void push(T data)
    {
        if (isFull())
        {
            cout << "Can't add " << data << ". Stack is full." << endl;
        }
        else
        {
            list.push_back(data);
            topItem = data;
        }
    }

    optional<T> pop()
    {
        if (isEmtpy())
        {
            return nullopt;
        }

        list.pop_back();
        topItem = list.back();
        return topItem;
    }

    bool isFull()
    {
        return list.size() == maxSize;
    }

    bool isEmtpy()
    {
        return list.size() == 0;
    }

    void printStack()
    {
        for (int i = list.size() - 1; i >= 0; i--)
        {
            string checkTop = list[i] == topItem ? "(top)" : "";
            cout << list[i] << " ";
        }

        cout << endl;
    }

private:
    vector<T> list;
    T topItem;
};

namespace stack
{
    void test()
    {
        Stack<int> stack = Stack<int>(10);
        cout << stack.peek().value_or(0) << endl;

        stack.push(10);
        stack.push(9);
        stack.push(8);
        stack.push(7);
        stack.push(6);
        stack.push(5);
        stack.push(4);
        stack.push(3);
        stack.push(2);
        stack.push(1);
        stack.push(11);

        cout << "last item is " << stack.peek().value_or(0) << endl;
        stack.printStack();
        stack.pop().value_or(0);

        cout << "last item is " << stack.peek().value_or(0) << endl;

        stack.printStack();
    }
}

#endif