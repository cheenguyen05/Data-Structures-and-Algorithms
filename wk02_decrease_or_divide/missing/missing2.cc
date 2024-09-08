#include <cstdlib>
#include <iostream>
#include "test.hh"

int searchSmallestMissing(int* A, int left, int right){
    //TODO: your code here
    //return missing value OR
    //return NO_VALUE_MISSING if no value is missing
    if (left > right) {
        return left; 
    }

    int mid = (left + right) / 2;

    if (A[mid] == mid) {
        return searchSmallestMissing(A, mid + 1, right);
    } else {
        return searchSmallestMissing(A, left, mid - 1);
    }
}
