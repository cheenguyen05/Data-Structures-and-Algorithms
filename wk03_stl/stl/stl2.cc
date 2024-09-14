#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


/**
 * @brief sort a given vector to an descending order
 *
 * @param v a vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortDesc(std::vector<int>& v)
{
    try {
        // Use std::sort to sort the vector in ascending order
        std::sort(v.begin(), v.end(), std::greater<int>());
        return EXIT_SUCCESS;
    } catch (...) {
        // Catch any exceptions and return EXIT_FAILURE if an error occurs
        return EXIT_FAILURE;
    }
}

