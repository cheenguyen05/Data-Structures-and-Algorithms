#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


/**
 * @brief Remove from vector v all elements with value less than the limit
 * @param v a vector whose values are to be erased if less than limit
 * @param limit a threshold whose lower values are removed
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int removeLessThan(std::vector<int>& v, int limit)
{
    // Use std::remove_if to move elements less than 'limit' to the end
    auto new_end = std::remove_if(v.begin(), v.end(), [limit](int value) {
        return value < limit;
    });

    // Erase the elements from the new end to the actual end
    v.erase(new_end, v.end());

    // If the code reaches this point, everything went OK
    return EXIT_SUCCESS;
}

