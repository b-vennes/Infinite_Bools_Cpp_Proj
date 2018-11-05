//  infiniteBools.cpp
//
//  Author: Steven R. Vegdahl, October 2018
//  Author: Branden Vennes
//

#include <cstddef>
#include <string>
#include "infiniteBools.h"

using namespace std;

/**
 * constructor for linked list node
 */
LinkedListNode::LinkedListNode(bool value, LinkedListNode* next, int index) : value(value), next(next), index(index) {
    refCount = 1;
}

/**
 * no-argument constructor
 */
InfiniteBools::InfiniteBools():
negHeader(NULL), nonNegHeader(NULL), defaultNegValue(false), defaultNonNegValue(false) {
    nonNegHeader = new LinkedListNode(false, NULL, 0);
    //cout << "Created new positive header for the list\n";
}

/**
 * 3-argument constructor
 */
InfiniteBools::InfiniteBools(bool n, bool z, bool p):
negHeader(NULL), nonNegHeader(NULL), defaultNegValue(n), defaultNonNegValue(p) {
    nonNegHeader = new LinkedListNode(z, NULL, 0);
}

/**
 * 
 */
InfiniteBools::InfiniteBools(const InfiniteBools& list):
defaultNegValue(list.defaultNegValue), defaultNonNegValue(list.defaultNonNegValue) {

    // copy nodes from neg list
    if (list.negHeader != NULL) {

        // create a new negative header
        negHeader = new LinkedListNode(list.negHeader->value, NULL, list.negHeader->index);

        LinkedListNode* copyFromNode = list.negHeader;
        LinkedListNode* copyToNode = negHeader;

        while (copyFromNode->next != NULL) {
            LinkedListNode* nextNode = new LinkedListNode(copyFromNode->next->value, NULL, copyFromNode->next->index);
            copyToNode->next = nextNode;
            copyToNode = nextNode;

            copyFromNode = copyFromNode->next;
        }
    }

    // copy nodes from pos list
    if (list.nonNegHeader != NULL) {
        nonNegHeader = new LinkedListNode(list.nonNegHeader->value, NULL, list.nonNegHeader->index);

        LinkedListNode* copyFromNode = list.nonNegHeader;
        LinkedListNode* copyToNode = nonNegHeader;

        while (copyFromNode->next != NULL) {
            LinkedListNode* nextNode = new LinkedListNode(copyFromNode->next->value, NULL, copyFromNode->next->index);
            copyToNode->next = nextNode;
            copyToNode = nextNode;

            copyFromNode = copyFromNode->next;
        }
    }
}

/**
 * 
 */
InfiniteBools::~InfiniteBools() {
    // delete our linked lists
    LinkedListNode* currNode = negHeader;

    while (currNode != NULL) {
        LinkedListNode* nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }

    currNode = nonNegHeader;

    while (currNode != NULL) {
        LinkedListNode* nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
}

/**
 * array index reference operation
 */
bool& InfiniteBools::operator[](int idx) {

    LinkedListNode* currNode;

    // determine positive or negative path
    if (idx >= 0) {
        currNode = nonNegHeader;  
    }
    else {
        currNode = negHeader;
    }

    // linked list is empty
    if (currNode == NULL) {
        if (idx < 0) {
            negHeader = new LinkedListNode(defaultNegValue, NULL, idx);
            return negHeader->value;
        }
        else {
            nonNegHeader = new LinkedListNode(defaultNonNegValue, NULL, idx);
            return negHeader->value;
        } 
        
    }

    while (currNode -> next != NULL) {
        // if we find the node for this index
        if (currNode->index == idx) {
            // return the boolean reference
            return currNode->value;
        }
        // if our index is bigger than this node and smaller than the next
        else if (abs(currNode->index) <= abs(idx) && abs(currNode->next->index) > abs(idx)) {
            // create a new node between this one and the next one
            // and return the node's boolean reference

            // positive index
            if (idx >= 0) {
                LinkedListNode* newPosNode = new LinkedListNode(defaultNonNegValue, currNode->next, idx);
                currNode->next = newPosNode;
                return newPosNode->value;
            }
            else {
                LinkedListNode* newNegNode = new LinkedListNode(defaultNegValue, currNode->next, idx);
                currNode->next = newNegNode;
                return newNegNode->value;
            }
        }
        currNode = currNode->next;
    }

    // reach this point if we have hit the last node and need to append a new one to the end
    if (idx == currNode->index) {
        return currNode->value;
    }
    else {
        if (idx >= 0) {
            LinkedListNode* lastPosNode = new LinkedListNode(defaultNonNegValue, NULL, idx);
            currNode->next = lastPosNode;
            return lastPosNode->value;
        }
        else {
            LinkedListNode* lastNegNode = new LinkedListNode(defaultNegValue, NULL, idx);
            currNode->next = lastNegNode;
            return lastNegNode->value;
        }
    }
}

/**
 * output operator
 */
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


