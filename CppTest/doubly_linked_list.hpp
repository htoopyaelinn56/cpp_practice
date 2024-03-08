#ifndef doubly_linked_list_hpp
#define doubly_linked_list_hpp

#include <iostream>
#include "node.hpp"
#include "singly_linked_list.hpp"

using namespace std;

template <typename T>
class DoublyLinkedList : public SinglyLinkedList<T>
{
public:
    Node<T> *insert(T data)
    {
        Node<T> *new_node = new Node<T>(data);

        if (this->head == nullptr)
        {
            this->head = new_node;
            this->tail = new_node;
        }
        else
        {
            Node<T> *temp = this->head;
            new_node->next = temp;
            this->head = new_node;
            temp->previous = this->head;
        }
        return this->head;
    }

    Node<T> *insert_after(Node<T> *node, T data)
    {

        Node<T> *new_node = new Node<T>(data);

        Node<T> *temp = node;
        Node<T> *next_node = node->next;
        node->next = new_node;
        new_node->previous = temp;

        if (next_node != nullptr)
        {
            new_node->next = next_node;
            next_node->previous = new_node;
        }
        return new_node;
    }

    Node<T> *insert_before(Node<T> *node, T data)
    {

        if (node == this->head)
        {
            insert(data);
            return this->head;
        }

        Node<T> *new_node = new Node<T>(data);

        Node<T> *temp = node;
        Node<T> *previous_node = temp->previous;
        temp->previous = new_node;
        new_node->next = temp;
        previous_node->next = new_node;
        new_node->previous = previous_node;

        return new_node;
    }

    Node<T> *insert_last(T data)
    {
        Node<T> *new_node = new Node<T>(data);

        if (this->head == nullptr)
        {
            this->head = new_node;
            this->tail = new_node;
        }
        else
        {
            Node<T> *temp = this->tail;
            temp->next = new_node;
            new_node->previous = temp;
            this->tail = new_node;
        }
        return new_node;
    }
};

namespace doubly_linked_list
{
    void test()
    {
        DoublyLinkedList<int> d;

        Node<int> *n1 = d.insert(1);
        Node<int> *n2 = d.insert(2);
        Node<int> *n3 = d.insert(3);

        d.print_list(); // 3 2 1

        d.insert_after(n2, 200);
        d.print_list(); // 3 2 200 1

        d.insert_after(n3, 300);
        d.print_list(); // 3 300 2 200 1

        d.insert_after(n1, 0);
        d.print_list(); // 3 300 2 200 1 0

        Node<int> *n0 = d.insert_before(n3, -1);
        d.print_list(); // -1 3 300 2 200 1 0

        d.insert_before(n3, 333);
        d.print_list(); // -1 3 333 300 2 200 1 0

        d.insert_last(10000);
        cout << "tail is " << d.tail->data << endl;
        d.print_list(); // -1 3 333 300 2 200 1 0 10000
    }
} // namespace doubly_linked_list

#endif