#include <iostream>

using namespace std;

template <typename T>
struct Node{
    T data;
    Node<T>* next;
};


template <typename T>
class ForwardList{
    private:
        Node<T>* head;
        int nodes;
    public:
        ForwardList(){
            head = nullptr;
            nodes = 0;
        }
        ~ForwardList(){delete[] head;}
        T front(){return head->data;}
        T back(){
            Node<T>* temp = head;
            while (temp->next != nullptr){temp = temp->next;}
            return temp->data;
        }
        int size(){return nodes;}
        void push_back(T data){
            Node<T> *nuevo = new Node<T>;
            nuevo->next = nullptr;
            nuevo->data = data;
            if (head==nullptr){head=nuevo;}
            else{
                Node<T>* temp = head;
                while(temp->next != nullptr) temp=temp->next;
                temp->next = nuevo;
            }
            nodes++;
        }
        T& operator[](int pos){
            Node<T>* iter = head;
            for (int i = 0; i < pos; i++) iter=iter->next;
            return iter->data;
        }
};