#include<iostream>
#include<ostream>
#include<string>
#include<math.h>

using namespace std;


template <typename T>
class LinearList {
    private:
        T* elements;
    public:
        int length;

        LinearList(); // Done
        
        int Search(T element);
        int Find(T element, int index);
        
        int Add(T element);
        
        void RawArray();

        bool isEmpty(){ return length == 0; }

        LinearList<T> RemoveAt(T element, int index);
        LinearList<T> InsertAt(T element, int index);

        T ElementAt(int index);
};

template <class T>
LinearList<T>::LinearList(){
    elements = new T[0];
    length = 0;
}

template <class T>
void LinearList<T>::RawArray(){
    for (int i = 0; i < length; i++){
        cout << elements[i] << " ";
    }
    cout << endl;
}

template <class T>
LinearList<T> LinearList<T>::InsertAt(T element, int index){
    T* newArr = new T[length + 1];

    int overhead = 0;

    for (int i = 0; i < length + 1; i++){
        if (overhead == 0){
            if (i != index){
                newArr[i] = elements[i];
            } else {
                newArr[i] = element;
                overhead++;
            }
        } else {
            newArr[i] = elements[i - 1];
        }
    }

    delete [] elements;
    elements = newArr;
    
    length++;

    newArr = NULL;

    return *this;
}

template <class T>
int LinearList<T>::Add(T element){
    T* newArr = new T[length + 1];

    for (int i = 0; i < length; i++){
        newArr[i] = elements[i];
    }
    newArr[length] = element;

    elements = newArr;
    
    length++;
    
    newArr = NULL;

    return 0;
}


template <class T>
T LinearList<T>::ElementAt(int index){
    return elements[index];
}

int TestCases(){
    LinearList<int> linearList;
    int a[] = {213,452,987,47,19,3873,2840,2373};
    int pass = 0;
    int fail = 0;
    
    for (int i = 0; i < 8; i++){
        cout << "Adding " << a[i] << " to list \'linearList\'..." << endl;
        linearList.Add(a[i]);
        cout << "length now is : " << linearList.length << endl;
    }

    cout << "Inserting \'245\' at index \'6\''..." << endl;
    linearList.InsertAt(245, 6);
    cout << "printing raw array representation of linearList..." << endl;
    linearList.RawArray();

    cout << endl;
    
    cout << "Verifying elements from linearList..." << endl;
    for (int i = 0; i < linearList.length; i++){
        if (a[i] == linearList.ElementAt(i)){
            cout << "Verified at " << i << " | element : " << linearList.ElementAt(i) << endl;
            pass++;
        } else {
            cout << "Failed verification of element at " << i << endl;
            fail++;
        }
    }

    cout << "Testing complete" << endl;
    cout << "Passed : " << pass << " Failed : " << fail << endl;


}

int main() {
    TestCases();
}