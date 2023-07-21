#include<iostream>
#include<cstdlib>
#include<cmath>
#include<ctime>

using namespace std;

const int NUMBERS_SIZE = 50000;

int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}
//prints out everything
void displayOutput(int numbers[], int NUMBER_SIZE){
   
    cout<<endl<<"Array elements are:"<<endl;
    for(int i=0;i<NUMBER_SIZE;i++){
        cout<<" "<<numbers[i];
    }

}

//splits the array up 
int partition(int numbers[], int start, int end){
    int pivotIndex = (start + end) / 2;
    int pivot = numbers[pivotIndex];
    int len = start;
    int ran = end;

    while (len <= ran){
        while (numbers[len] < pivot){
            len++;
        }
        while (numbers[ran] > pivot){
            ran--;
        }
        if (len <= ran){
            swap(numbers[len], numbers[ran]);
            len++;
            ran--;
        }
    }
    return len;
}

//midpoint quicksort
void Quicksort_midpoint(int numbers[], int start, int end){
    if (start >= end){
        return;
    }
    int j = partition(numbers, start, end);
    Quicksort_midpoint(numbers, start, j - 1);
    Quicksort_midpoint(numbers, j, end);
}

//medianOfThree quicksort
void Quicksort_medianOfThree(int numbers[], int start, int end){
    if (start >= end){
        return;
    }
        
    int j = partition(numbers, start, end);
    Quicksort_medianOfThree(numbers, start, j - 1);
    Quicksort_medianOfThree(numbers, j, end);
}

//InsertionSort
void InsertionSort(int arr[], int n)
{
    int arrNum, j;
    for (int i = 1; i < n; i++){
        arrNum = arr[i];
        j = i - 1;
 
        while (j >= 0 && arr[j] > arrNum){
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = arrNum;
    }
}





int main(){

    int arr1[NUMBERS_SIZE],arr2[NUMBERS_SIZE],arr3[NUMBERS_SIZE];
    fillArrays(arr1,arr2,arr3);

    const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000;
    clock_t Start1 = clock();
    Quicksort_midpoint(arr1,0,NUMBERS_SIZE-1);
    clock_t End1 = clock();
    int elapsedTime1 = (End1 - Start1)/CLOCKS_PER_MS;

    cout<<"Quicksort_midpoint algorithm runtime: "<<elapsedTime1<<endl;
    clock_t Start2 = clock();
    Quicksort_medianOfThree(arr2,0,NUMBERS_SIZE);
    clock_t End2 = clock();
    int elapsedTime2 = (End2 - Start2)/CLOCKS_PER_MS;

    cout<<"Quicksort_medianOfThree algorithm runtime: "<<elapsedTime2<<endl;
    clock_t Start3 = clock();
    InsertionSort(arr3,NUMBERS_SIZE);
    clock_t End3 = clock();
    int elapsedTime3 = (End3 - Start3)/CLOCKS_PER_MS;

    cout<<"InsertionSort algorithm runtime: "<<elapsedTime3<<endl;

}