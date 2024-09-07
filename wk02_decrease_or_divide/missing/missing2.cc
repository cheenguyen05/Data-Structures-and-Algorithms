#include <cstdlib>
#include <iostream>
#include "test.hh"

int searchSmallestMissing(int* A, int left, int right){
    //TODO: your code here
    //return missing value OR
    //return NO_VALUE_MISSING if no value is missing
    if (left > right) {
        return NO_VALUE_MISSING; // Trường hợp không còn phần tử nào để kiểm tra
    }

    int mid = left + (right - left) / 2;

    // Giá trị kỳ vọng tại chỉ số mid
    int expectedValue = A[left] + mid - left;

    if (A[mid] != expectedValue) {
        // Nếu giá trị tại mid không bằng giá trị kỳ vọng, giá trị kỳ vọng là số bị thiếu
        return expectedValue;
    } else {
        // Nếu giá trị tại mid khớp với giá trị kỳ vọng, tiếp tục tìm kiếm trong nửa mảng bên phải
        return searchSmallestMissing(A, mid + 1, right);
    }
}
