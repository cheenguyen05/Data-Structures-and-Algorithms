/**
 * iteration1.cc
 *
 * Print all items of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration1.hh"
using namespace std;


void printAllItems(const list<int>& lst)
{
    // ADD YOUR CODE HERE
     for (auto it = lst.begin(); it != lst.end(); ++it) 
    {
        cout << *it << " ";
    }
    // Print a new line at the end
    cout << endl;
}
