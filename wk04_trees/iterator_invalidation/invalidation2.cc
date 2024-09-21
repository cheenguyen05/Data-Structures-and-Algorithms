#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Erases every second item from the vector. Example: {1, 2, 3, 4} -> {1, 3}
 *
 * @param vec vector where every second item is erased.
 */
void eraseEverySecond(std::vector<int>& vec) {
// Use std::remove_if to remove every second element.
    vec.erase(
        remove_if(vec.begin(), vec.end(), [index = 0](int) mutable {
            return index++ % 2 == 1;  // Erase every element with odd index.
        }),
        vec.end()
    );
}

