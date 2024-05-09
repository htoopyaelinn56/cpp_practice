//
//  singly_linked_list.hpp
//  CppTest
//
//  Created by Htoo Pyae Linn on 27/02/2024.
//

#ifndef singly_linked_list_hpp
#define singly_linked_list_hpp

#include <iostream>
#include <vector>
#include "node.hpp"

using namespace std;

template <typename T>
class SinglyLinkedList
{
public:
    Node<T> *head;
    Node<T> *tail;

    SinglyLinkedList()
    {
        this->head = nullptr;
        this->tail = nullptr;
    }

    Node<T> *insert(T data)
    {
        Node<T> *new_node = new Node<T>(data);

        if (head == nullptr)
        {
            this->head = new_node;
            this->tail = new_node;
        }
        else
        {
            Node<T> *temp = this->head;
            new_node->next = temp;
            this->head = new_node;
        }
        return head;
    }

    Node<T> *insert_at(int index, T data)
    {
        if (index == 0)
        {
            insert(data);
            return head;
        }

        return __common_insert(index, data);
    }

    Node<T> *insert_node(Node<T> *node, T data)
    {

        if (node == head)
        {
            insert(data);
            return head;
        }

        int index = index_of(node);
        return __common_insert(index, data);
    }

    Node<T> *insert_last(T data)
    {
        Node<T> *new_node = new Node<T>(data);

        if (head == nullptr)
        {
            this->head = new_node;
            this->tail = new_node;
        }
        else
        {
            Node<T> *temp = this->tail;
            temp->next = new_node;
            this->tail = new_node;
        }

        return this->tail;
    }

    void print_list()
    {
        Node<T> *current = head;

        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    Node<T> *element_at(int index)
    {
        if (index <= 0)
        {
            return head;
        }
        else
        {
            Node<T> *current = head;
            for (int i = 0; i <= index; i++)
            {
                if (i == index)
                {
                    break;
                }

                if (current != nullptr && current->next != nullptr)
                {
                    current = current->next;
                }
                else
                {
                    current = nullptr;
                }
            }
            return current;
        }
    }

    int index_of(Node<T> *node)
    {
        int counter = 0;

        Node<T> *current = head;

        while (current != node)
        {
            current = current->next;
            counter++;
        };

        return counter;
    }

    void delete_node(Node<T> *node)
    {
        if (node == head)
        {
            head = head->next;
            return;
        }

        int index_of_deleting_node = index_of(node);
        __common_delete(index_of_deleting_node);
    }

    void delete_at(int index)
    {
        if (index == 0)
        {
            head = head->next;
            return;
        }
        __common_delete(index);
    }

    vector<T> to_vec()
    {
        vector<T> vec;

        Node<T> *current = head;
        while (current != nullptr)
        {
            vec.push_back(current->data);
            current = current->next;
        }

        return vec;
    }

    void from_vec(vector<T> vec)
    {
        for (auto i = vec.rbegin(); i != vec.rend(); ++i)
            this->insert(*i);
    }

private:
    void
    __common_delete(int index)
    {
        if (head != nullptr)
        {
            Node<T> *previous_node = element_at(index - 1);
            Node<T> *next_node = element_at(index + 1);

            previous_node->next = next_node;
        }
    }

    Node<T> *__common_insert(int index, T data)
    {
        Node<T> *previous_node = element_at(index - 1);
        Node<T> *node_at_index = element_at(index);
        Node<T> *temp = node_at_index;

        Node<T> *new_node = new Node<T>(data);

        if (node_at_index != nullptr && previous_node != nullptr)
        {
            node_at_index = new_node;
            new_node->next = temp;
            previous_node->next = new_node;

            return new_node;
        }
        else
        {
            return nullptr;
        }
    }
};

namespace singly_linked_list
{
    void test()
    {
        SinglyLinkedList<int> n;
        Node<int> *node_1 = n.insert(5);
        Node<int> *node_2 = n.insert(3);
        Node<int> *node_3 = n.insert(1);
        n.print_list(); // 1 3 5

        Node<int> *node_4 = n.insert_node(node_2, 150);
        n.print_list(); // 1 150 3 5

        n.delete_at(1);
        n.print_list(); // 1 3 5

        n.delete_node(node_1);
        n.print_list(); // 1 3

        vector<int> vec = n.to_vec();

        for (auto i = vec.begin(); i != vec.end(); ++i)
            cout << *i << " "; // 1 3

        cout << endl;

        SinglyLinkedList<int> n1;
        vector<int> vec_1;
        vec_1.push_back(1);
        vec_1.push_back(2);
        vec_1.push_back(3);
        vec_1.push_back(4);

        cout << "vec 1 => ";
        for (auto i = vec_1.begin(); i != vec_1.end(); ++i)
            cout << *i << " "; // 1 2 3 4

        n1.from_vec(vec_1);
        cout << endl
             << "linked list => ";
        n1.print_list(); // 1 2 3 4

        n1.insert_last(1000); // 1000
        n1.print_list();      // 1 2 3 4 1000
        n1.insert_last(2000); // 2000
        n1.print_list();      // 1 2 3 4 1000 2000
    }
}

#endif /* singly_linked_list_hpp */
