//
//  singly_linked_list.hpp
//  CppTest
//
//  Created by Htoo Pyae Linn on 27/02/2024.
//

#ifndef singly_linked_list_hpp
#define singly_linked_list_hpp

#include <iostream>
using namespace std;

template <typename T>
class Node{
public:
    T data;
    Node* next;
    
    Node(T data){
        this->data = data;
        this->next = nullptr;
    }
    
    void print(){
        cout << data << endl;
    }
};

template <typename T>
class SinglyLinkedList{
public:
    Node<T>* head;
    
    SinglyLinkedList(){
        this->head = nullptr;
    }
    
    Node<T>* insert(T data){
        Node<T>* new_node = new Node(data);
        
        if(head == nullptr){
            this->head = new_node;
        }else{
            Node<T>* temp = this->head;
            new_node->next = temp;
            this->head = new_node;
            
        }
        return head;
        
    }
    
    Node<T>* insert_at(int index,T data){
        
        if(index == 0){
            insert(data);
            return head;
        }
        
        return _common_insert(index,data);
    }
    
    Node<T>* insert_node(Node<T>* node,T data){
        
        if(node == head){
            insert(data);
            return head;
        }
        
        int index = index_of(node);
       return _common_insert(index,data);
    }
    
    void print_list(){
        Node<T>* current = head;
        
        while(current != nullptr){
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
    
    Node<T>* element_at(int index){
        if(index <= 0){
            return head;
        }else{
            Node<T>* current = head;
            for(int i = 0;i <= index;i++){
                if( i == index){
                    break;
                }
                
                if(current != nullptr && current->next != nullptr){
                    current = current->next;
                }else{
                    current = nullptr;
                }
            }
            return current;
        }
    }
    
    int index_of(Node<T>* node){
        int counter = 0;
        
        Node<T>* current = head;
        
        while(current != node){
            current = current->next;
            counter++;
        };
        
        return counter;
        
    }
    
    void delete_node(Node<T>* node){
        
        if(node == head){
            head = head->next;
            return;
        }
        
        int index_of_deleting_node = index_of(node);
        _common_delete(index_of_deleting_node);
    }
    
    void delete_at(int index){
        if(index == 0){
            head = head->next;
            return;
        }
        _common_delete(index);
        
    }
    
private:
    void _common_delete(int index){
        if(head != nullptr){
            Node<T>* previous_node = element_at(index - 1);
            Node<T>* next_node = element_at(index + 1);
            
            previous_node->next = next_node;
        }
    }
    
    Node<T>* _common_insert(int index,T data){
        Node<T>* previous_node = element_at(index - 1);
        Node<T>* node_at_index = element_at(index);
        Node<T>* temp = node_at_index;
        
        Node<T>* new_node = new Node(data);
        
        if(node_at_index != nullptr && previous_node != nullptr){
            node_at_index = new_node;
            new_node->next = temp;
            previous_node->next = new_node;
            
            return new_node;
        }else{
            return nullptr;
        }
    }
    
};




namespace singly_linked_list {
    void test(){
        SinglyLinkedList<int> n;
        Node<int>* node_1 = n.insert(5);
        Node<int>* node_2 = n.insert(3);
        Node<int>* node_3 = n.insert(1);
        n.print_list(); // 1 3 5
        
        Node<int>* node_4 = n.insert_node(node_2, 150);
        n.print_list(); // 1 150 3 5
        
        n.delete_at(1);
        n.print_list(); // 1 3 5
        
        n.delete_node(node_1);
        n.print_list(); // 1 3
    }
}

#endif /* singly_linked_list_hpp */


