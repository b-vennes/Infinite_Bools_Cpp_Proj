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
 * 
 * @param value the boolean value associated with this node
 * @param next the next linked list node 
 * @param index the associated index in the infinite bools list that this node occupies
 */
LinkedListNode::LinkedListNode(bool value, LinkedListNode* next, int index) : value(value), next(next), index(index) {
}

/**
 * no-argument constructor
 */
InfiniteBools::InfiniteBools():
negHeader(NULL), nonNegHeader(NULL), defaultNegValue(false), defaultNonNegValue(false) {
    // create a node at index 0 with a false default value
    nonNegHeader = new LinkedListNode(false, NULL, 0);
}

/**
 * 3-argument constructor
 * 
 * @param n the default value fro negative indices
 * @param z the default value for the zero index
 * @param p the default value for positive indices
 */
InfiniteBools::InfiniteBools(bool n, bool z, bool p):
negHeader(NULL), nonNegHeader(NULL), defaultNegValue(n), defaultNonNegValue(p) {
    // create a node at index 0 with the given value (z) of boolean
    nonNegHeader = new LinkedListNode(z, NULL, 0);
}

/**
 * copy constructor
 * 
 * @param list the InfiniteBools object to copy
 */
InfiniteBools::InfiniteBools(const InfiniteBools& list):
defaultNegValue(list.defaultNegValue), defaultNonNegValue(list.defaultNonNegValue) {

    // copy nodes from negative list
    if (list.negHeader != NULL) {

        // create a new negative header
        negHeader = new LinkedListNode(list.negHeader->value, NULL, list.negHeader->index);

        // keep track of current node in new object to mirror current node in object being copied
        LinkedListNode* copyFromNode = list.negHeader;
        LinkedListNode* copyToNode = negHeader;

        // create a new node with the next pointer's values, while the next node is not empty
        while (copyFromNode->next != NULL) {
            LinkedListNode* nextNode = new LinkedListNode(copyFromNode->next->value, NULL, copyFromNode->next->index);
            copyToNode->next = nextNode;
            copyToNode = nextNode;

            copyFromNode = copyFromNode->next;
        }
    }

    // copy nodes from positive list
    if (list.nonNegHeader != NULL) {

        // create a new positives header
        nonNegHeader = new LinkedListNode(list.nonNegHeader->value, NULL, list.nonNegHeader->index);

        // create a new node with the next pointer's values, while the next node is not empty
        LinkedListNode* copyFromNode = list.nonNegHeader;
        LinkedListNode* copyToNode = nonNegHeader;

        // create a new node with the next pointer's values, while the next node is not empty, as done with the negatives list
        while (copyFromNode->next != NULL) {
            LinkedListNode* nextNode = new LinkedListNode(copyFromNode->next->value, NULL, copyFromNode->next->index);
            copyToNode->next = nextNode;
            copyToNode = nextNode;

            copyFromNode = copyFromNode->next;
        }
    }
}

/**
 * class destructor for InfiniteBools array
 */
InfiniteBools::~InfiniteBools() {

    // delete negatives list
    LinkedListNode* currNode = negHeader;

    // delete each node one by one
    while (currNode != NULL) {
        LinkedListNode* nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }

    // delete positives list
    currNode = nonNegHeader;

    // delete each node one by one
    while (currNode != NULL) {
        LinkedListNode* nextNode = currNode->next;
        delete currNode;
        currNode = nextNode;
    }
}

/**
 * array index reference operation
 * 
 * @param idx the index of the boolean value to retrieve
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

    // linked list is empty, will need to create a new header
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

    // linked list is not empty, need to traverse list to find if the node already exists or needs to be created
    while (currNode -> next != NULL) {

        // found a node with the index already created
        if (currNode->index == idx) {
            return currNode->value;
        }

        // need to create anew node between two nodes in the linked list
        else if (abs(currNode->index) <= abs(idx) && abs(currNode->next->index) > abs(idx)) {

            // positive index, use default positive value
            if (idx >= 0) {
                LinkedListNode* newPosNode = new LinkedListNode(defaultNonNegValue, currNode->next, idx);
                currNode->next = newPosNode;
                return newPosNode->value;
            }
            
            // negative index, use default negative value
            else {
                LinkedListNode* newNegNode = new LinkedListNode(defaultNegValue, currNode->next, idx);
                currNode->next = newNegNode;
                return newNegNode->value;
            }
        }

        currNode = currNode->next;
    }

    // reached end of list, so a new node must be appended to the end, or it is the last node in the list

    // last node in list is the one we are searching for
    if (idx == currNode->index) {
        return currNode->value;
    }

    // need to append a new node to the end of the list
    else {

        // positive index, use default positive value
        if (idx >= 0) {
            LinkedListNode* lastPosNode = new LinkedListNode(defaultNonNegValue, NULL, idx);
            currNode->next = lastPosNode;
            return lastPosNode->value;
        }

        // negative index, use default negative value
        else {
            LinkedListNode* lastNegNode = new LinkedListNode(defaultNegValue, NULL, idx);
            currNode->next = lastNegNode;
            return lastNegNode->value;
        }
    }
}

/**
 * output operator override
 * 
 * @param os the output stream
 * @param obj the infinite bools object to output
 */
std::ostream& operator <<(std::ostream& os, InfiniteBools const& obj) {

    // start by adding all the interesting booleans from the negative list
    LinkedListNode* curr = obj.negHeader;

    string negOutput = "";

    // the previous important index node
    int lastIndex = -1;

    // the current important index node
    int currIndex;

    // determine what the default negative value is
    char defNegOut;
    if (obj.defaultNegValue) {
        defNegOut = 'T';
    }
    else {
        defNegOut = 'F';
    }

    // create a string of formatted boolean values associated with negative indices
    while(curr != NULL)
    {
        // only care to print node if it is different than default
        if (curr->value != obj.defaultNegValue) {
            currIndex = curr->index;

            // fill in default indices between the last interesting node and this one
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

    // the output associated with the zero index of our list
    string zeroOutput = "";

    // zero index is always header node in positive list
    curr = obj.nonNegHeader;

    // get 0 index value
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

    // determine the positive output string
    while (curr != NULL) {

        // only care about non-default nodes
        if (curr->value != obj.defaultNonNegValue) {
            currIndex = curr->index;

            // fill in default values between the last important nodes
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

    // format the edges of each string correctly

    if (negOutput.length() > 0) {

        // character on left side of the negative output string
        char stringStart = negOutput[0];

        // if the left end of the negative string is not the default, we need to add the default boolean letter
        if (stringStart != defNegOut) {
            negOutput = defNegOut + negOutput;
        } 
    }

    if (posOutput.length() > 0) {

        // character on right side of the positive output string
        char stringEnd = posOutput[posOutput.length() - 1];

        // if the right end of the positive string is not the default, we need to add the default boolean letter
        if (stringEnd != defPosOut) {
            posOutput += defPosOut;
        } 
    }

    // build our string output and return it
    string output = "[..." + negOutput + "<" + zeroOutput + ">" + posOutput + "...]";

    os << output;
    return os;
}


