#include<cstdlib>
#include<iostream>
#include<string>
#include<math.h>

using namespace std;

void printArr(int* a, int length);
int* bubbleSort(int* input, int k);
int* selectionSort(int* input, int k);
int* bucketSort(int* input, int k);

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
    
    for (int i = 0; i < ARR_LEN; i++){
        array[i] = i;
        //array[i] = rand() % 1000 + 1;
    }

    cout << endl << "Sorting array using selectionSort..." << endl;
    printArr(selectionSort(array, ARR_LEN), ARR_LEN);
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

int* selectionSort(int* input, int k){
    int* temp = input;
    for (int i = 0; i < k; i++){
        for (int j = i; j < k; j++){
            temp = input[j] <= *temp ? &input[j] : temp; 
        }

        if (input[i] < *temp){
            input[i] ^= *temp;
            *temp ^= input[i];
            input[i] ^= *temp;   

            *temp = input[i+1];     
        }
    }
    return input;
}

int* bucketSort(int* input, int k){
    int max = *input;
    for (int i = 0; i < k; i++){
        max = max > input[i] ? max : input[i];
    }
    int* bucketArr = new int[max];
    
    for (int i = 0; i < k; i++){
        bucketArr[i]++;
    }

    int* result = new int[k];

    for (int i = 0; i < max; i++){
        if (bucketArr[i]>0){
            
        }
    }
    return input;
}