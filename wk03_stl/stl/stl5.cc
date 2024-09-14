#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


/**
 * @brief Arrange vector in three subsequent sections:
 *        - those divisible by three (asc order)
 *        - those whose reminder is 1 (asc order)
 *        - those whose reminder is 2 (asc order)
 * @param v vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortMod3(std::vector<int>& v)
{
    // Phân chia vector thành 3 nhóm dựa trên giá trị dư của phép chia cho 3
    auto candiv3 = std::stable_partition(v.begin(), v.end(), [](int n) { return n % 3 == 0; });
    auto rem1end = std::stable_partition(candiv3, v.end(), [](int n) { return n % 3 == 1; });

    // Sắp xếp từng nhóm theo thứ tự tăng dần
    std::sort(v.begin(), candiv3);    // Các phần tử chia hết cho 3
    std::sort(candiv3, rem1end);      // Các phần tử có dư là 1
    std::sort(rem1end, v.end());        // Các phần tử có dư là 2

    return EXIT_SUCCESS;
}

