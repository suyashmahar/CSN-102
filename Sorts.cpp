#include<cstdlib>
#include<iostream>
#include<string>

using namespace std;

void printArr(int* a, int length);
int* bubbleSort(int* input, int k);

int ARR_LEN = 100;

int main(){
    // Initialize array with random data
    srand(time(NULL));

    int* array = new int[ARR_LEN];
    for (int i = 0; i < ARR_LEN; i++){
        array[i] = rand() % 1000 + 1;
    }
    
    printArr(array, ARR_LEN);
    cout << endl << "Sorting array using bubbleSort..." << endl;
    printArr(bubbleSort(array, ARR_LEN), ARR_LEN);
    cout  << endl << "exiting..." << endl;
}


// Prints given array in single line
void printArr(int* a, int length){
    for (int i = 0; i < length; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

int* bubbleSort(int* input, int k) {
    for (int i = 0; i < k-1; i++) {
        for (int j = 0; j < k-1-i; j++) {
            if (input[j] > input[j+1]){
                input[j] ^= input[j+1];
                input[j+1] ^= input[j];
                input[j] ^= input[j+1];
            }
        }
    }
    return input;
}
