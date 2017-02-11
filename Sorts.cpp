#include<cstdlib>
#include<iostream>
#include<queue>
#include<string>
#include<math.h>

using namespace std;

void printArr(int* input, int length, bool del);
int* copyArray(int* input, int k);
int* bubbleSort(int* input, int k);
int* selectionSort(int* input, int k);
int* bucketSort(int* input, int k);
int* radixSort(int* input, int k);

int ARR_LEN = 100;

int main(){
    // Initialize array with random data
    srand(time(NULL));

    int* array = new int[ARR_LEN];
    for (int i = 0; i < ARR_LEN; i++){
        array[i] = rand() % 1000 + 1;
    }

    cout << "Random array used for sorting is : " << endl;
    printArr(array, ARR_LEN, false);

    cout << endl << "Sorting array using bubbleSort..." << endl;
    printArr(bubbleSort(copyArray(array, ARR_LEN), ARR_LEN), ARR_LEN, false);
    

    cout << endl << "Sorting array using selectionSort..." << endl;
    printArr(selectionSort(copyArray(array, ARR_LEN), ARR_LEN), ARR_LEN, false);
    cout  << endl;

    cout << endl << "Sorting array using bucketSort..." << endl;
    printArr(bucketSort(copyArray(array, ARR_LEN), ARR_LEN), ARR_LEN, false);
    cout  << endl;

    cout << endl << "Sorting array using radixSort..." << endl;
    printArr(radixSort(copyArray(array, ARR_LEN), ARR_LEN), ARR_LEN, false);
    cout  << endl;
    for (int i = 0; i < ARR_LEN; i++){
        array[i] = rand() % 1000 + 1;
    }
}

// returns a copy of input array 
int* copyArray(int* input, int k){
    int* result = new int[k];
    for (int i = 0; i < k; i++){
        result[i] = input[i];    
    }
    return result;
}



// Prints given array in single line
// and then deletes it.
void printArr(int* input, int length, bool del){
    for (int i = 0; i < length; i++){
        cout << input[i] << " ";
    }
    cout << endl;

    if (del){
        delete[] input;
        input = NULL;
    }
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
    for (int i = 0; i < k-1; i++){
        for (int j = i+1; j < k; j++){
            temp = input[j] <= *temp ? &input[j] : temp; 
        }

        if (input[i] > *temp){
            // Swaps number at i with that at temp using XOR            
            input[i] ^= *temp;
            *temp ^= input[i];
            input[i] ^= *temp;   
        }

            // temp is assigned first value from next set
            *temp = input[i+1];     
    }
    
    return input;
}

// Bubble sort implementation to sort positive numbers in c++
int* bucketSort(int* input, int k){
    // Finds and stores the maximum number that appears
    // among the input set.
    int max = *input;

        for (int i = 0; i < k; i++) {
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
    // tracks index of input array  
    //        |         
    //        | tracks index of result array      
    //        |       |       
    //        |       |  equals to condition so that largest doesn't get left out       
    //        |       |       | 
    //        *       *       * 
    for (int i = 0, j  = 0; i <= max && j <= max; i++){
        for (int l = 0; l < bucketArr[i]; l++){
            result[j++] = i;
        }
    }
    return result;
}

// Implementation of https://www.youtube.com/watch?v=GUHGMtNo6RQ 
int* radixSort(int* input, int k){
    int count = 0;
    // number of digits in a number is (floor(log10(number)) + 1)
    int maxDigits = 0;

    for (int i = 0; i < k; i++){
        int digits = floor(log10(input[i])) + 1;
        maxDigits = maxDigits > digits ? maxDigits : digits;
    }    

    for (int i = 0; i < maxDigits; i++){
        queue<int>* aux = new queue<int>[10];

        for (int j = 0; j < k; j++){
            // gets i th least significant digit of the number
            int digit = (input[j]%((int)pow(10, i+1)))/(int)pow(10, i);
            count++;
            aux[digit].push(input[j]);
        }
        // Rebuilding the array
        for (int j = 0, l = 0; j < 10; j++){
            while (aux[j].size()){
                input[l++] = aux[j].front();
                aux[j].pop();
            }
        }
    }
    return input;
}