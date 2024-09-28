#include <iterator>
#include <vector>
#include <map>
#include <algorithm>


/**
 * @brief Sums up the values of the vector cumulatively, storing cumulative sum
 *        of the vector in a map, where the keys are the unique vector items,
 *        and the value is the last cumulative sum when that value was last
 *        encountered. (example: {4, 5, 4, 6} => {{4, 13}, {5, 9}, {6, 19}}).
 *
 * @param vec vector which is used for the sum operation.
 * @return std::map<int, int> sums - the sums of each cumulation stored in
 *         a map as values, vector values used as keys.
 */
std::map<int, int> cumulativeSums(const std::vector<int>& v) {
    std::map<int, int> sums;
    int cumulativeSum = 0; // To keep track of the cumulative sum

    for (const int& value : v) {
        cumulativeSum += value; // Add current value to cumulative sum
        sums[value] = cumulativeSum; // Store the cumulative sum for the current value
    }

    return sums; // Return the map with cumulative sums
}