#include<iostream>
#include<string>
#include<queue>

using namespace std;

queue<int> q;

//template <class T>
int qpop() {
    for (int i = 0; i < q.size()-1; i++){
        q.push(q.front());
        q.pop();
    }
    int result = q.front();
    q.pop();
    return result; 
}

//template <class T>
void qpush(int element){
    q.push(element);
}

int main(){
    for (int i = 0; i < 10; i++){
        qpush(i);
    }
    for (int i = 0; i < 10; i++){
        cout << qpop();
    }
}