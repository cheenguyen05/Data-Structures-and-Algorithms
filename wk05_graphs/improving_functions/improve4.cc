#include <iterator>
#include <vector>
#include <algorithm>
#include <random>


//---- Some utilities
using iter = std::vector<int>::iterator;
using RNG = std::default_random_engine;

/**
 * @brief Sorts a given vector using a 3 part randomized quicksort algorithm.
 *        Randomization is used to avoid worst case (where the pivot value is
 *        chosen poorly).
 *
 * HINT: The way randomization is implemented can be changed. Shuffle may not
 *       be the only or the best way to implement randomization.
 *
 * @param begin an iterator that points to the beginning part of the sequence where the quicksort is performed.
 * @param end an iterator that points to the end part of the sequence where the quicksort is performed
 * @param rng the random number generator that can be used
 */
void randomizedThreePartQuicksort(iter begin, iter end, RNG& rng)
{
    // Base case: if range is empty or has one element, return
    if (begin >= end) return;

    // Randomly pick a pivot by swapping the first element with a random element in the range
    std::uniform_int_distribution<int> dist(0, end - begin - 1);
    int randomIndex = dist(rng); // Select random index
    std::iter_swap(begin, begin + randomIndex); // Swap first element with randomly chosen element
    auto pivot = *begin; // Use the first element as the pivot

    // Partition the range into three parts:
    iter middle1 = std::partition(begin + 1, end,
        [pivot](int val) { return val < pivot; });
    iter middle2 = std::partition(middle1, end,
        [pivot](int val) { return !(pivot < val); });

    // Recursively sort the left and right partitions
    randomizedThreePartQuicksort(begin + 1, middle1, rng);
    randomizedThreePartQuicksort(middle2, end, rng);
}
