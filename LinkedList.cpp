#include<iostream>
#include<string>

using namespace std;

template <class T>
class Node{
    public:
        Node(T data, Node<T> *link);
        ~Node();
        T data;
        Node<T> *link; 
};

template <typename T>
Node<T>::Node(T data, Node<T> *link){
    this->data = data;
    this->link = link;
}
template <typename T>
Node<T>::~Node(){
    //cout << "Node with address " << this << " and referring to : " << this->link << " destructed" << endl;
}

template <class T>
class LinkedList{
    public:
        LinkedList();
        ~LinkedList();
        bool isEmpty();  // Done
        int Length() const; 
        bool Find(int k, T data) const; // Done
        int Search(const T data) const; // Done
        LinkedList<T> Delete(int k); 
        LinkedList<T> Insert(const T data);
        LinkedList<T> Insert(int k, const T data);
        T ElementAt(int index);
        int length;
    private:
        Node<T> *first = NULL;
        Node<T> *last = NULL;
        Node<T> NodeAt(int index);
        int listSize;
};

template <typename T>
LinkedList<T>::LinkedList(){
    length = 0;
}
template <typename T>
LinkedList<T>::~LinkedList(){
    //cout << "Object destructed!" << endl;
}
template <typename T>
bool LinkedList<T>::isEmpty(){
    return (length == 0);
}
template <typename T>
bool LinkedList<T>::Find(int k, T data) const{
    Node<T> *current = this->first;
    int index = 0;
    while (current->link != NULL && current->data !=data){
        index++;
    }

    if (current->link == NULL){
        return -1;
    }
    
    return index;
}
template <typename T>
int LinkedList<T>::Search(const T data) const{
    Node<T> *current = this->first;
    
    int index = 0;

    while (current->data != data){
        index++;
    }

    if (current->link == NULL){
        return -1;
    }
    return index;

}
template <typename T>
LinkedList<T> LinkedList<T>::Insert(const T data){
    Node<T> *node = new Node<T>(data, NULL);

    if (length == 0){
        first = node;
        last = node;
    } else {
        last->link = node;
        last = node;
    }

    length++;

    return *this;
}
template <typename T>
LinkedList<T> LinkedList<T>::Insert(int k, const T data){
    if (k < 0 || k >= length)
        throw std::out_of_range("Invalid index");

    Node<T> node(data, NULL);
    
    int index = -1;
    
    Node<T> *current = this->first;
    while (index != k-1){
        current = current->link;
        index++;
    }

    node.link = current->link;
    current->link = &node;

    if (k == 0)
        first = &node;

    if (k == this->length-1)
        last = &node;
    
    length++;

    return *this;
}

template <typename T>
T LinkedList<T>::ElementAt(int index){
    if (index < 0 || index >= length)
        throw std::out_of_range("Invalid index");
    
    Node<T> current = *first;

    int counter = 0;
    
    while (counter != index){
        current = *(current.link);
        counter++;
    }

    return current.data;
}

int main(){
    LinkedList<int> linkedList;
    int a[] = {213,452,987,47,19,3873,2840,2373};
    int pass = 0;
    int fail = 0;
    
    for (int i = 0; i < 8; i++){
        cout << "Adding " << a[i] << " to list \'linkedList\'..." << endl;
        linkedList.Insert(a[i]);
        cout << "length now is : " << linkedList.length << endl;
    }

    cout << "Inserting \'245\' at index \'6\''..." << endl;
    linkedList.Insert(6, 245);
    
    cout << "Verifying elements from linkedList..." << endl;
    for (int i = 0; i < linkedList.length; i++){
        if (a[i] == linkedList.ElementAt(i)){
            cout << "Verified at " << i << " | element : " << linkedList.ElementAt(i) << endl;
            pass++;
        } else {
            cout << "Failed verification of element at " << i << endl;
            fail++;
        }
    }

    cout << "Testing complete" << endl;
    cout << "Passed : " << pass << " Failed : " << fail << endl;

}