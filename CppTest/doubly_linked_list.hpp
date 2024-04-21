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

        if (this->tail == node)
        {
            this->tail = new_node;
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
        return insert_after(this->tail, data);
    }

    void delete_node(Node<T> *node)
    {

        if (this->head == nullptr)
        {
            return;
        }

        if (this->head == node)
        {
            this->head = node->next;
            node = nullptr;
        }
        else if (this->tail == node)
        {
            this->tail = node->previous;
            this->tail->next = nullptr;
            node = nullptr;
        }
        else
        {
            node->previous->next = node->next;
            node->next->previous = node->previous;
            node = nullptr;
        }
    }

    void delete_first()
    {
        delete_node(this->head);
    }

    void delete_last()
    {
        delete_node(this->tail);
    }
};

namespace doubly_linked_list
{
    void test()
    {
        DoublyLinkedList<int> d;

        d.delete_node(new Node<int>(-999)); // nothing happened

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
        d.print_list(); // -1 333 3 300 2 200 1 0

        d.insert_last(10000);
        d.print_list(); // -1 333 3 300 2 200 1 0 10000
        cout << "head is " << d.head->data << endl;
        cout << "tail is " << d.tail->data << endl;

        d.delete_node(n0);
        cout << "head is " << d.head->data << endl; // 333 3 300 2 200 0 10000

        d.delete_node(n1);
        d.print_list(); // -333 3 300 2 200 0 10000

        d.delete_node(d.tail);
        d.print_list(); // -333 3 300 2 200 0

        d.delete_first();
        d.print_list(); // 3 300 2 200 0

        d.delete_last();
        d.print_list(); // 3 300 2 200
    }
} // namespace doubly_linked_list

#endif