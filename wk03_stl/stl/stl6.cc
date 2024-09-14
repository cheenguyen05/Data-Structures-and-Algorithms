#include <iterator>
#include <map>
#include <algorithm>

#include "test.hh" // NOT_FOUND constant

using namespace std;


/**
 * @brief From a map find the first element, whose value is at least given limit
 *        regardless of the key of the element. Return only the value or
 *        NOT_FOUND if none of the values match the the search criteria.
 * @param m map that is scanned trough
 * @param given limit for the values to search
 * @return int the real found value
 */
int findAtLeastGiven(std::map<std::string, int>& m, int given)
{
    // Use std::find_if to find the first element that matches the criteria
    auto it = std::find_if(m.begin(), m.end(), [given](const std::pair<std::string, int>& p) {
        return p.second >= given;
    });

    // Check if an element was found
    if (it != m.end()) {
        // Return the value of the found element
        return it->second;
    } else {
        // Return NOT_FOUND if no element meets the criteria
        return NOT_FOUND;
    }
}

