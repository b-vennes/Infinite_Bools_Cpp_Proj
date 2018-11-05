//  infiniteBools.h
//
//  Author: Steven R. Vegdahl, October 2018
//  Author: Branden Vennes
//

#ifndef infiniteBools_h
#define infiniteBools_h

#include <iostream>

using namespace std;

// "forward" class declaration
class InfiniteBools;

// linked-list node helper-class
class LinkedListNode {
private:
    // the boolean value for this linked list node
    bool value;
    // the array index that this node represents
    int index;
    // the next pointer for this node
    LinkedListNode* next;
public:
    // no argument constructor
    LinkedListNode();
    // 3 argument constructor for initializing sections of the infinite bools list
    LinkedListNode(bool value, LinkedListNode* next, int index);
    
    // allow the InfiniteBools class private access
    friend class InfiniteBools;
    friend std::ostream& operator <<(std::ostream& os, InfiniteBools const& obj);
};

// InfiniteBools class
class InfiniteBools {
    
private:
    // linked list headers
    LinkedListNode* nonNegHeader; // list for non-negative-index values
    LinkedListNode* negHeader; // list for negative-index values
    
    // default values
    bool defaultNegValue; // default negative-index value
    bool defaultNonNegValue; // default non-negative-index value
    
public:
    InfiniteBools(); // no-argument constructor
    InfiniteBools(bool n, bool z, bool p); // 3-argument constructor
    InfiniteBools(const InfiniteBools&); // copy constructor
    ~InfiniteBools(); // destructor

    bool& operator[](int idx); // "array-reference" operator
    
    // friend declaration so output operator can access us
    friend std::ostream& operator <<(std::ostream& os, InfiniteBools const& obj);
};

// output operator for InfiniteBools class
std::ostream& operator <<(std::ostream& os, InfiniteBools const& obj);


#endif /* infiniteBools_h_h */
