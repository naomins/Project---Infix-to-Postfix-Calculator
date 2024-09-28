//  Stack.h

#ifndef STACK_H
#define STACK_H

#include "Node.h"
#include <iostream>

class Stack {
private:
    Node *head = nullptr;
    void deleteNodesRecursively(Node* node); // helper for recursive deletion
    
public:
    // Constructors
    Stack(); // default
    Stack(Node *ptr); // overloaded
    Stack (const Stack& copy); // Copy constructor

    // Accessors
    Node *getHead() const {return head;}
    
    // Mutators
    void setHead(Node *h1){head = h1;}
    
    // Overloaded operators
    friend std::ostream &operator<<(std::ostream&, const Stack&); // << for printing stack
    
    Stack &operator<<(Node*); // for pushing to stack
    Stack &operator>>(Node*&); // >> for popping from stack
    
    // Destructor
    ~Stack(); // Destructor to recursively delete linked list
};

#endif
