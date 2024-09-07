#include <cstdlib>
#include <iostream>
#include "test.hh"

int searchSmallestMissingIteration(int* arr, int size){
    //TODO: your code here
    //return missing value OR
    //return NO_VALUE_MISSING if no value is missing
    for (int i = 0; i < size; i++) {
        if (arr[i] != i) {
            return i;  
        }
    }
    return NO_VALUE_MISSING;
}
