#ifndef circular_linked_list_hpp
#define circular_linked_list_hpp

#include <iostream>
#include "doubly_linked_list.hpp"
#include "node.hpp"

using namespace std;

template <typename T>
class CircularLinkedList : public DoublyLinkedList<T>
{
public:
    Node<T> *insert(T data)
    {
        Node<T> *new_node = new Node<T>(data);

        if (this->head == nullptr)
        {
            this->head = new_node;
            this->tail = new_node;

            this->head->next = this->tail;
            this->head->previous = this->tail;
            this->tail->next = this->head;
            this->tail->previous = this->head;
        }
        else
        {
            Node<T> *temp = this->head;
            new_node->next = temp;
            this->head = new_node;
            temp->previous = this->head;

            this->head->next = temp;
            this->head->previous = this->tail;
            this->tail->next = this->head;
            this->tail->previous = temp;
        }
        return this->head;
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

    void print_list()
    {
        Node<T> *current = this->head;

        do
        {
            bool is_head = current == this->head;
            bool is_tail = current == this->tail;
            string value = is_head ? ":head" : is_tail ? ":tail"
                                                       : "";
            cout << current->data << "(prev=" << current->previous->data << ",next=" << current->next->data << "" << value << ") ";
            current = current->next;
        } while (current != this->head);

        cout << endl;
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
            Node<T> *result_node = node->next;
            this->head = result_node;
            this->tail->next = result_node;
            this->head->previous = this->tail;
            node = nullptr;
            result_node = nullptr;
        }
        else if (this->tail == node)
        {
            this->tail = node->previous;
            this->tail->next = this->head;
            this->head->previous = this->tail;
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

namespace circular_linked_list
{
    void test()
    {
        CircularLinkedList<int> c;

        Node<int> *n1 = c.insert(1);
        cout << "head of c is " << c.head->data << endl;
        cout << "head\'s next is is " << c.head->next->data << endl;
        cout << "head\'s previous is is " << c.head->previous->data << endl;
        cout << "tail of c is " << c.tail->data << endl;
        cout << "tail\'s next is is " << c.tail->next->data << endl;
        cout << "tail\'s previous is is " << c.tail->previous->data << endl;
        cout << endl;
        Node<int> *n2 = c.insert(2);
        cout << "head of c is " << c.head->data << endl;
        cout << "head\'s next is is " << c.head->next->data << endl;
        cout << "head\'s previous is is " << c.head->previous->data << endl;
        cout << "tail of c is " << c.tail->data << endl;
        cout << "tail\'s next is is " << c.tail->next->data << endl;
        cout << "tail\'s previous is is " << c.tail->previous->data << endl;
        cout << endl;
        Node<int> *n3 = c.insert_before(c.head, 3);
        cout << "head of c is " << c.head->data << endl;
        cout << "head\'s next is is " << c.head->next->data << endl;
        cout << "head\'s previous is is " << c.head->previous->data << endl;
        cout << "tail of c is " << c.tail->data << endl;
        cout << "tail\'s next is is " << c.tail->next->data << endl;
        cout << "tail\'s previous is is " << c.tail->previous->data << endl;
        c.print_list();
        cout << endl;
        Node<int> *n4 = c.insert_after(n3, 444);
        c.print_list();
        cout << endl;
        Node<int> *n5 = c.insert_before(n2, 555);
        c.print_list();
        cout << endl;
        c.delete_first();
        c.print_list();
        cout << "deleting =======>" << endl;
        c.delete_last();
        c.print_list();
        cout << endl;
        c.delete_last();
        c.print_list();
        cout << endl;
        c.delete_last();
        c.print_list();
        cout << endl;
    }
}

#endif