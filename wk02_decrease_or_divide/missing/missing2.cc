#include <cstdlib>
#include <iostream>
#include "test.hh"

int searchSmallestMissing(int* A, int left, int right){
    //TODO: your code here
    //return missing value OR
    //return NO_VALUE_MISSING if no value is missing
    if (left == right)
    {
        if (A[left] != left + A[0])
        {
           return A[left]-1;
        }
    }
    else
    {
        // Calculate middle index
        int middle = left + (right - left) / 2;

        // If value at middle index matches the middle, the missing number is on the right
        if (A[middle] == middle + A[0])
        {
           return searchSmallestMissing(A, middle + 1, right);
        }
        else if(A[middle] > middle + A[0])
        {
            return searchSmallestMissing(A, left, middle);
        }
    }
    return NO_VALUE_MISSING;
}
