//  infiniteBools.cpp
//
//  Author: Steven R. Vegdahl, October 2018
//  Author: Branden Vennes
//

#include <cstddef>
#include <string>
#include "infiniteBools.h"

using namespace std;

// constructor for linked list node
LinkedListNode::LinkedListNode(bool value, LinkedListNode* next, int index) : value(value), next(next), index(index) {
    refCount = 1;
}

// no-argument constructor
InfiniteBools::InfiniteBools():
negHeader(NULL), nonNegHeader(NULL), defaultNegValue(false), defaultNonNegValue(false) {
    nonNegHeader = new LinkedListNode(false, NULL, 0);
    //cout << "Created new positive header for the list\n";
}

// 3-argument constructor
InfiniteBools::InfiniteBools(bool n, bool z, bool p):
negHeader(NULL), nonNegHeader(NULL), defaultNegValue(n), defaultNonNegValue(p) {
    nonNegHeader = new LinkedListNode(z, NULL, 0);
    //cout << "Created new positive header for the list\n";
}

InfiniteBools::InfiniteBools(const InfiniteBools& list):
defaultNegValue(list.defaultNegValue), defaultNonNegValue(list.defaultNonNegValue) {

    // copy nodes from neg list
    if (list.negHeader != NULL) {

        // create a new negative header
        cout << "Creating a negative header for the new list at index " << list.negHeader->index << ".\n";
        negHeader = new LinkedListNode(list.negHeader->value, NULL, list.negHeader->index);

        LinkedListNode* copyFromNode = list.negHeader;
        LinkedListNode* copyToNode = negHeader;

        while (copyFromNode->next != NULL) {
            cout << "Attaching new negative node to the list at index " << copyFromNode->next->index << ".\n";
            LinkedListNode* nextNode = new LinkedListNode(copyFromNode->next->value, NULL, copyFromNode->next->index);
            copyToNode->next = nextNode;
            copyToNode = nextNode;

            copyFromNode = copyFromNode->next;
        }
    }

    // copy nodes from pos list
    if (list.nonNegHeader != NULL) {

        cout << "Creating a positive header for the new list at index " << list.nonNegHeader->index << ".\n";
        nonNegHeader = new LinkedListNode(list.nonNegHeader->value, NULL, list.nonNegHeader->index);

        LinkedListNode* copyFromNode = list.nonNegHeader;
        LinkedListNode* copyToNode = nonNegHeader;

        while (copyFromNode->next != NULL) {
            cout << "Attaching new positive node to the list at index " << copyFromNode->next->index << ".\n";
            LinkedListNode* nextNode = new LinkedListNode(copyFromNode->next->value, NULL, copyFromNode->next->index);
            copyToNode->next = nextNode;
            copyToNode = nextNode;

            copyFromNode = copyFromNode->next;
        }
    }
}

// array index reference operation
bool& InfiniteBools::operator[](int idx) {

    //cout << "Looking for node at index " << idx << ".\n";

    LinkedListNode* currNode;

    // determine positive or negative path
    if (idx >= 0) {
        //cout << "Looking for positive node.\n";
        currNode = nonNegHeader;  
    }
    else {
        //cout << "Looking for negative node.\n";
        currNode = negHeader;
    }

    // linked list is empty
    if (currNode == NULL) {
        //cout << "No nodes found in linked list.\n";
        if (idx < 0) {
            //cout << "Created new negative node at index.\n";
            negHeader = new LinkedListNode(defaultNegValue, NULL, idx);
            return negHeader->value;
        }
        else {
            //cout << "Created new positive node at index.\n";
            nonNegHeader = new LinkedListNode(defaultNonNegValue, NULL, idx);
            return negHeader->value;
        } 
        
    }

    while (currNode -> next != NULL) {
        //cout << "Current search node is " << currNode->index << ".\n";
        // if we find the node for this index
        if (currNode->index == idx) {
            // return the boolean reference
            //cout << "Found pre-existing node.\n";
            return currNode->value;
        }
        // if our index is bigger than this node and smaller than the next
        else if (abs(currNode->index) <= abs(idx) && abs(currNode->next->index) > abs(idx)) {
            // create a new node between this one and the next one
            // and return the node's boolean reference

            // positive index
            if (idx >= 0) {
                //cout << "Creating new positive node in middle of list.\n";
                LinkedListNode* newPosNode = new LinkedListNode(defaultNonNegValue, currNode->next, idx);
                currNode->next = newPosNode;
                return newPosNode->value;
            }
            else {
                //cout << "Creating new negative node in middle of list.\n";
                LinkedListNode* newNegNode = new LinkedListNode(defaultNegValue, currNode->next, idx);
                currNode->next = newNegNode;
                return newNegNode->value;
            }
        }
        currNode = currNode->next;
    }

    // reach this point if we have hit the last node and need to append a new one to the end
    if (idx == currNode->index) {
        //cout << "Found pre-existing node.\n";
        return currNode->value;
    }
    else {
        if (idx >= 0) {
            //cout << "Creating new positive node at end of positive list.\n";
            LinkedListNode* lastPosNode = new LinkedListNode(defaultNonNegValue, NULL, idx);
            currNode->next = lastPosNode;
            return lastPosNode->value;
        }
        else {
            //cout << "Creating new negative node at end of negative list.\n";
            LinkedListNode* lastNegNode = new LinkedListNode(defaultNegValue, NULL, idx);
            currNode->next = lastNegNode;
            return lastNegNode->value;
        }
    }
}

// output operator
std::ostream& operator <<(std::ostream& os, InfiniteBools const& obj) {

    LinkedListNode* curr = obj.negHeader;

    // print off all negative values
    string negOutput = "";
    int lastIndex = -1;
    int currIndex;

    // determine what the default negative output is
    char defNegOut;
    if (obj.defaultNegValue) {
        defNegOut = 'T';
    }
    else {
        defNegOut = 'F';
    }

    while(curr != NULL)
    {
        // only care to print node if it is different than default
        if (curr->value != obj.defaultNegValue) {
            currIndex = curr->index;

            for (int i = currIndex; i < lastIndex; i++) {
                negOutput = defNegOut + negOutput;
            }

            if (curr->value) {
                negOutput = 'T' + negOutput;
            }
            else {
                negOutput = 'F' + negOutput;
            }

            lastIndex = curr->index;
        }
        curr = curr->next;
    }

    //cout << "Negative List = " << negOutput << "\n";

    string zeroOutput = "";

    curr = obj.nonNegHeader;

    // get 0 value
    if (obj.nonNegHeader->value) {
        zeroOutput = 'T';
    }
    else {
        zeroOutput = 'F';
    }

    lastIndex = 0;
    curr = curr->next;

    string posOutput = "";

    // determine what the default positive output is
    char defPosOut;
    if (obj.defaultNonNegValue) {
        defPosOut = 'T';
    }
    else {
        defPosOut = 'F';
    }

    // determine the positive output
    while (curr != NULL) {

        if (curr->value != obj.defaultNonNegValue) {
            currIndex = curr->index;
            //cout << "Current output index = " << currIndex << ".\n";

            for (int i = lastIndex + 1; i < currIndex; i++) {
                posOutput += defPosOut;
            }

            if (curr->value) {
                posOutput += 'T';
            }
            else {
                posOutput += 'F';
            }

            lastIndex = curr->index;
        }
        
        curr = curr->next;
    }

    // make sure that endings all match up
    
    // match negative to zero
    if (negOutput.length() == 0) {
        if (obj.defaultNegValue != obj.nonNegHeader->value) {
            if (obj.defaultNegValue) {
                negOutput = 'T';
            }
            else {
                negOutput = 'F';
            }
        }
    }

    // match positve to zero
    if (posOutput.length() == 0) {
        if (obj.defaultNonNegValue != obj.nonNegHeader->value) {
            if (obj.defaultNegValue) {
                posOutput = 'T';
            }
            else {
                posOutput = 'F';
            }
        }
    }

    // make sure end of negative array is formatted correctly
    if (negOutput.length() > 0) {
        char stringStart = negOutput[0];

        if (stringStart != defNegOut) {
            negOutput = defNegOut + negOutput;
        } 
    }

    // make sure end of positive array is formatted correctly
    if (posOutput.length() > 0) {
        char stringStart = posOutput[posOutput.length() - 1];

        if (stringStart != defPosOut) {
            posOutput += defPosOut;
        } 
    }

    // put together the output
    string output = "[..." + negOutput + "<" + zeroOutput + ">" + posOutput + "...]";

    os << output;
    return os;
}


