#ifndef node_hpp
#define node_hpp

template <typename T>
class Node
{
public:
    T data;
    Node *next;
    Node *previous; // not in singly linked list

    Node(T data)
    {
        this->data = data;
        this->next = nullptr;
        this->previous = nullptr;
    }

    void print()
    {
        std::cout << data << std::endl;
    }
};

#endif