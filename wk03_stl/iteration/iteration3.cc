/**
 * iteration3.cc
 *
 * Print beginning half of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration3.hh"
using namespace std;


void printHalf(const list<int>& lst)
{
    // ADD YOUR CODE HERE
    // size
    int size = lst.size();
    // find index of the element in the mid
    int halfSize = size / 2;

    // iterator point to the first index
    auto it = lst.begin();
    
    // loop thru the first half
    for (int i = 0; i < halfSize; ++i) {
        cout << *it << " "; 
        ++it; 
    }
    
    cout << endl; 
}
