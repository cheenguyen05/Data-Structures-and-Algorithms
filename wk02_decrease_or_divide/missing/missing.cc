#include <cstdlib>
#include <iostream>
#include "test.hh"


int searchSmallestMissingIteration(int* arr, int size){
    //TODO: your code here
    //return missing value OR
    //return NO_VALUE_MISSING if no value is missing
    if (size == 0) {
        return NO_VALUE_MISSING;
    }

    int expectedValue = arr[0];

    for (int i = 0; i < size; i++) {
        if (arr[i] != expectedValue) {
            return expectedValue;
        }
        // Cập nhật giá trị kỳ vọng cho lần kiểm tra tiếp theo
        expectedValue++;
    }

    // Nếu không có giá trị nào bị thiếu trong khoảng từ giá trị đầu tiên đến giá trị cuối cùng
    return NO_VALUE_MISSING;
}