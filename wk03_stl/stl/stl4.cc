#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


/**
 * @brief Return an iterator which points to the last even integer of the vector
 *        If the value is not found, return v.rend()
 *
 * @param v the vector to be scanned through
 * @return std::vector<int>::reverse_iterator
 */
std::vector<int>::reverse_iterator findLastEven(std::vector<int>& v)
{
    // Sử dụng std::find_if với reverse iterator để tìm số chẵn
    auto it = std::find_if(v.rbegin(), v.rend(), [](int n) { return n % 2 == 0; });

    // Nếu tìm thấy số chẵn, trả về iterator trỏ đến nó
    if (it != v.rend()) {
        return it;
    }
    
    // Nếu không tìm thấy số chẵn, trả về v.rend()
    return v.rend();
}

