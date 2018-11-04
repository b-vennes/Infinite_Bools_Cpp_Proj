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
    arr[3] = true;
    arr[6] = true;
    arr[-10] = false;
    arr[12] = false;
    arr[-5] = true;

    /*
    // print the contents before modifying
    cout << "======== 'true' elements ========" << endl;
    for (int i = -15; i <= 15; i++) {
        if (arr[i]) {
            cout << "found flag at " << i << endl;
        }
    }
    
    InfiniteBools arr2(arr);
    
    arr2[2] = true;
    
    // print the arrays
    cout << "========= original array ========" << endl;
    cout << arr << endl;
    cout << "========= copy of array ========" << endl;
    cout << arr2 << endl;

    */
    
    // return a "success" exit status
    return 0;
}
