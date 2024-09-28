//  Node.h

#ifndef NODE_H
#define NODE_H

#include "Data.h"

class Node {
private:
    Data payload;
    Node *next = nullptr;
    
public:
    // Constructors
    Node(){}; // default
    Node(Data p1){payload = p1;} // overloaded
    
    // Accessors
    Data getPayload() const {return payload;}
    Node* getNext() const {return next;}
    
    // Mutators
    void setPayload(Data pl) {payload = pl;}
    void setNext(Node *n){next = n;}
};

#endif
