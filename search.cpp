#include<iostream>
#include<string>

using namespace std;

int binarySearch(int* inputArr, int element, int low, int high);

int main(){
    int *sampleArray = new int[10];

    for (int i = 0; i < 10; i++){
        sampleArray[i] = i+1;
    }

    cout << binarySearch(sampleArray, 8, 0, 9);

}

int binarySearch(int* inputArr, int element, int low, int high){
    if (low <= high){
        if (inputArr[low] == element) return low;
        if (inputArr[high] == element) return high;
        
        int mid = low + (high-low)/2;

        if (inputArr[mid] == element) return mid;
        
        if (inputArr[mid] < element){
            binarySearch(inputArr, element, mid+1, high);
        } 
        else if (inputArr[mid] > element){
            binarySearch(inputArr, element, low, mid-1);
        } 


    }
    else return -1;
}