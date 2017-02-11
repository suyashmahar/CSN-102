// Circular Linked List implementation in C++
#include<iostream>
#include<string>

using namespace std;

template<typename T>
class Node{
    private:
    public:
        Node<T> *left;
        Node<T> *right;
        T data;

        Node();
        Node(Node<T> *left, T data, Node<T> *right);
        ~Node();
};

template <class T>
Node<T>::Node(){
    this->left = NULL;
    this->right = NULL;
}

template <class T>
Node<T>::Node(Node<T> *left, T data, Node<T> *right){
    this->left = left;
    this->right = right;
}

template <class T>
Node<T>::~Node(){
    delete this->left;
    delete this->right;
    delete this->data;
}
template <typename T>
class CircularLinkedList{
    private:
        Node<T> *first;
    public:
        CircularLinkedList();
        ~CircularLinkedList();
        int length;
        CircularLinkedList<T>* Add(const T data);
        CircularLinkedList<T>* Insert(int k, const T data);
        int Find(int k, const T data);
        int Search(const T data);
        CircularLinkedList<T> Delete(int k);

        void print();
        void printReferences();
};

template <class T>
CircularLinkedList<T>::CircularLinkedList(){
    Node<T> *headNode = new Node<T>();
    
    headNode->left = headNode->right = headNode;
    headNode->data = 0;
    
    first = headNode; 

    length = 0;
}

template <class T>
CircularLinkedList<T>* CircularLinkedList<T>::Add(const T data){
    Node<T> *newNode = new Node<T>();
    
    newNode->left = first->left;
    newNode->left->right = newNode;
    newNode->right = first;
    newNode->data = data;
    
    first->left = newNode;
    
    length++;
    return this;
}
template<class T>
CircularLinkedList<T> *CircularLinkedList<T>::Insert(int k, const T data){
    if (k >= length || k < 0)
        throw out_of_range("Index does not exists.");
    Node<T> *newNode = new Node<T>();
    Node<T> *current = first;

    int index = 0;

    while (index != k+1){
        index++;
        current = current->right;
    }

    current->left->right = newNode;
    newNode->left = current->left;
    newNode->right = current;
    current->left = newNode;

    newNode->data = data;

    cout << data << endl;
 
    length++;

    return this;
}

template <class T>
void CircularLinkedList<T>::print(){
    Node<T> *current = first->right;
    while (current->right != first){
        cout << current->data << " ";
        current = current->right;
    }
    cout << endl;
}

template <class T>
void CircularLinkedList<T>::printReferences(){
    Node<T> *current = first->right;
    while (current->right != first){
        cout << current->left << "<-" <<  current << "->" << current->right << " | " << current->data << endl;
        current = current->right;
    }
    cout << endl;
}

int main(){
    CircularLinkedList<int> *newList = new CircularLinkedList<int>();
    for (int i = 0; i < 10; i++){   
        newList->Add((int)(i));
    }

    newList->Insert(8, 410);
    cout  << endl << "Length is: " << newList->length << endl;
    
    //newList->printReferences();
    newList->print();
}

