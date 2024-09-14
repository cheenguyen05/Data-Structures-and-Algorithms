#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh" // NOT_FOUND constant

using namespace std;


/**
 * @brief Find the median value of a given vector, whose elements are in random
 *        order. Return NOT_FOUND if the size of the vector is zero.
 *
 * @param v unsorted vector
 * @return int calculated median of parameter vector
 */
int findMedian(std::vector<int>& v)
{
    // Nếu vector trống, trả về NOT_FOUND
    if (v.size() == 0) {
        return NOT_FOUND;
    }
    // Sắp xếp vector
    std::sort(v.begin(), v.end());

    // Tìm median
    size_t n = v.size();
    
    // Nếu số phần tử là số lẻ
    if (n % 2 == 1) {
        return v[n / 2];  // Phần tử giữa
    }
    
    // Nếu số phần tử là số chẵn
    int mid1 = v[n / 2];
    int mid2 = v[n / 2 - 1];
    int median = std::floor((mid1 + mid2) / 2.0);  // Làm tròn xuống

    return median;

}

