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
        array[i] = rand() % 1000 + 1;
    }

    cout << endl << "Sorting array using selectionSort..." << endl;
    printArr(selectionSort(array, ARR_LEN), ARR_LEN);
    cout  << endl << "exiting..." << endl;
    for (int i = 0; i < ARR_LEN; i++){
        array[i] = rand() % 1000 + 1;
    }

    cout << endl << "Sorting array using bucketSort..." << endl;
    printArr(bucketSort(array, ARR_LEN), ARR_LEN);
    cout  << endl << "exiting..." << endl;
    for (int i = 0; i < ARR_LEN; i++){
        array[i] = rand() % 1000 + 1;
    }
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
                // Swaps number at j with j+1 using XOR
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
            // Swaps number at i with that at temp using XOR            
            input[i] ^= *temp;
            *temp ^= input[i];
            input[i] ^= *temp;   

            // temp is assigned first value from next set
            *temp = input[i+1];     
        }
    }
    return input;
}

// Bubble sort implementation to sort positive numbers in c++
int* bucketSort(int* input, int k){
    // Finds and stores the maximum number that appears
    // among the input set.
    int max = *input;
    for (int i = 0; i < k; i++){
        max = max > input[i] ? max : input[i];
    }

    // Creates new array of bucket
    int* bucketArr = new int[max+1];

    // Stores input into to corresponding bucket    
    for (int i = 0; i < k; i++){
        bucketArr[input[i]]++;
    }

    // Array that stores result to return
    int* result = new int[k];

    // Iterates over every bucket and fills result
    //
    // tracks index of result array  
    //        |         
    //        | tracks number of elements in bucket     
    //        |       |       
    //        |       |  equals to condition so that largest doesn't get left out       
    //        |       |       | 
    //        *       *       * 
    for (int i = 0, j  = 0; i <= max; i++){
        for (int l = 0; l < bucketArr[i]; l++){
            result[j++] = i;
        }
    }
    return result;
}

