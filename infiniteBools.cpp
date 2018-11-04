//  infiniteBools.cpp
//
//  Author: Steven R. Vegdahl, October 2018
//  Author: Branden Vennes
//

#include <cstddef>
#include "infiniteBools.h"

using namespace std;

// constructor for linked list node
LinkedListNode::LinkedListNode(bool value, LinkedListNode* next) : value(value), next(next) {
}

// no-argument consstructor
InfiniteBools::InfiniteBools():
negHeader(NULL), nonNegHeader(NULL), defaultNegValue(false), defaultNonNegValue(false) {
    nonNegHeader = new LinkedListNode(false, NULL);
    nonNegHeader->refCount++;
    nonNegHeader->index = 0;
    cout << "Created new positive header for the list\n";
}

// 3-argument consstructor
InfiniteBools::InfiniteBools(bool n, bool z, bool p):
negHeader(NULL), nonNegHeader(NULL), defaultNegValue(n), defaultNonNegValue(p) {
    nonNegHeader = new LinkedListNode(z, NULL);
    nonNegHeader->refCount++;
    nonNegHeader->index = 0;
    cout << "Created new positive header for the list\n";
}

// array index reference operation
bool& InfiniteBools::operator[](int idx) {

    cout << "looking for node at index " << idx << "\n";

    LinkedListNode* currNode;

    // determine positive or negative path
    if (idx >= 0) {
        cout << "looking for positive node.\n";
        currNode = nonNegHeader;  
    }
    else {
        cout << "looking for negative node.\n";
        currNode = negHeader;
    }

    // linked list is empty
    if (currNode == NULL) {
        cout << "no nodes found in linked list.\n";
        if (idx < 0) {
            cout << "created new negative node at index\n";
            negHeader = new LinkedListNode(defaultNegValue, NULL);
            negHeader->refCount++;
            return negHeader->value;
        }
        else {
            cout << "created new positive node at index\n";
            nonNegHeader = new LinkedListNode(defaultNonNegValue, NULL);
            nonNegHeader->refCount++;
            return negHeader->value;
        } 
        
    }

    while (currNode -> next != NULL) {
        // if we find the node for this index
        if (currNode->index == idx) {
            // return the boolean reference
            cout << "found pre-existing node.\n";
            return currNode->value;
        }
        // if our index is bigger than this node and smaller than the next
        else if (abs(currNode->index) <= abs(idx) && abs(currNode->next->index) > abs(idx)) {
            // create a new node between this one and the next one
            // and return the node's boolean reference

            // positive index
            if (idx >= 0) {
                cout << "creating new positive node.\n";
                LinkedListNode* newPosNode = new LinkedListNode(defaultNonNegValue, currNode->next);
                currNode->next = newPosNode;
                newPosNode->refCount++;
                return newPosNode->value;
            }
            else {
                cout << "creating new negative node.\n";
                LinkedListNode* newNegNode = new LinkedListNode(defaultNegValue, currNode->next);
                currNode->next = newNegNode;
                newNegNode->refCount++;
                return newNegNode->value;
            }
        }
    }

    // reach this point if we have hit the last node and need to append a new one to the end
    if (idx == currNode->index) {
        cout << "found pre-existing node.\n";
        return currNode->value;
    }
    else {
        if (idx >= 0) {
            cout << "creating new positive node.\n";
            LinkedListNode* lastPosNode = new LinkedListNode(defaultNonNegValue, NULL);
            currNode->next = lastPosNode;
            lastPosNode->refCount++;
            return lastPosNode->value;
        }
        else {
            cout << "creating new negative node.\n";
            LinkedListNode* lastNegNode = new LinkedListNode(defaultNegValue, NULL);
            currNode->next = lastNegNode;
            lastNegNode->refCount++;
            return lastNegNode->value;
        }
    }
}

// output operator
std::ostream& operator <<(std::ostream& os, InfiniteBools const& obj) {
    os << "This is dummied up";
    return os;
}
