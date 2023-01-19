// Q1.c – Assignment 03 – Aidan, Darling

#include <stdio.h>
#include <string.h>

// Finds the greatest value in the array
int getMax(int array[][3], int n, int arrayType) {
    int max = array[0][arrayType]; 
    for (int i = 1; i < n; i++){
        if (array[i][arrayType] > max) max = array[i][arrayType];
    }
    return max;
}



void countSort(int arr[][3], int size, int arrayType, int exp)
{
    int output[size][3]; 
    int i;
    int count[10] = {0};
 
    // Store count of occurrences in count[]
    for (i = 0; i < size; i++){
        count[(arr[i][arrayType] / exp) % 10]++;
    }
        
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++){
        count[i] += count[i - 1];
    }
        
 
    // Build the output array
    for (i = size - 1; i >= 0; i--) {
        for (int x = 0; x < 3; x++)
        {
            output[count[(arr[i][arrayType] / exp) % 10] - 1][x] = arr[i][x];
        }
        count[(arr[i][arrayType] / exp) % 10]--;
    }

    
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < size; i++){
        for (int x = 0; x < 3; x++)
        {
            arr[i][x] = output[i][x];
        }
        
    }
}

void radixsort(int array[][3], int size) {
    // Main function to implement radix sort 
    for (int i = 0; i < 3; i++)
    {
        int max = getMax(array, size, i); 
        for (int place = 1; max / place > 0; place *= 10) {
            countSort(array, size, i, place);
        }
    }

}

int main(){
    // Create array with values
    int arr[][3] = {{20, 1, 2014}, {25, 3, 2010}, {3, 12, 1676}, {18, 11, 1982}, {19, 4,2015},
    { 9, 7, 2015}, {12, 8, 2010}, {30, 8, 2010}, {21, 1, 2014}, {20, 7, 2014},{18, 11, 2020}};

    // Get size of array
    int size = sizeof(arr)/sizeof(arr[0]);

    // Call sorting array
    radixsort(arr, size);


    // Output list of sorted dates
    for (int i = 0; i < size; i++)
    {
        
        for (int j = 0; j < 3; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
        
    }

}