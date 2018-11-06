////////////////////////////////////////////////////////////////
//  main.cpp
//
//  main/driver program for testing the map class
//
//  author: Steven R. Vegdahl
//  author: Branden Vennes
//  version: 20 October 2018
////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include "infiniteBools.h"

using namespace std;

////////////////////////////////////////////////////////////////
// the main method: creates InfiniteBool objects, then uses, copies
// etc.
////////////////////////////////////////////////////////////////
int main(int argc, const char * argv[]) {

    // the object to use, initialized by default to all 'false'
    InfiniteBools arr;

    // set some values to be true, and a couple to be false
    arr[-4] = true;
    arr[8] = true;
    arr[12] = true;

    /*
    // print the contents before modifying
    cout << "======== 'true' elements ========" << endl;
    for (int i = -15; i <= 15; i++) {
        if (arr[i]) {
            cout << "found flag at " << i << endl;
        }
    }
    */
    InfiniteBools arr2(arr);
    
    // print the arrays
    cout << "========= original array ========" << endl;
    cout << arr << endl;
    cout << "========= copy of array ========" << endl;
    cout << arr2 << endl;

    InfiniteBools arr3 = arr;

    arr3[-4] = false;

    for (int i = 0; i < 100000000; i++) {
        InfiniteBools* newList = new InfiniteBools();
        (*newList)[1] = true;
        (*newList)[-10] = true;
        (*newList)[15] = true;
        delete newList;
    }

    if (arr[-4]) {
        cout << "value is true\n";
    }
    else {
        cout << "value is false\n";
    }
    
    // return a "success" exit status
    return 0;
}
