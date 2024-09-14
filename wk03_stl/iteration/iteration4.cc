/**
 * iteration4.cc
 *
 * Print all items of a list in a reverse order
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration4.hh"
using namespace std;


void printReverse(const list<int>& lst)
{
    // ADD YOUR CODE HERE
    // Tạo một reverse iterator cho danh sách
    for (auto it = lst.rbegin(); it != lst.rend(); ++it) {
        cout << *it << " "; // In giá trị của phần tử hiện tại và một khoảng trắng
    }
    
    cout << endl; // Xuống dòng sau khi in xong
}
