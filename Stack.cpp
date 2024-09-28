//  Stack.cpp

#include "Stack.h"
#include <iostream>

// Default constructor
Stack::Stack() {
    head = nullptr;
}

// Overloaded constructor with a parameter to set head
Stack::Stack(Node *ptr) {
    head = ptr;
}

// Copy constructor
Stack::Stack(const Stack& copy) {
    // If the other stack is empty, set head to nullptr and return
    if (copy.head == nullptr) {
        head = nullptr;
        return;
    }
    
    // Create copy of linked list in the other stack
    head = new Node(*copy.head); // create new node
    Node *current = head;
    Node *copyCurrent = copy.head->getNext(); // pointer to traverse other stack's linked list
    
    // Iterate over the other stack's linked list and copy each node
    while(copyCurrent != nullptr) {
        current->setNext(new Node(*copyCurrent)); // create a new node by copying payload of current node in other stack
        current = current->getNext(); // move ptr
        copyCurrent = copyCurrent->getNext(); // move ptr in other stack
        
    }
}

// Overloaded << operator for printing the stack
std::ostream &operator<<(std::ostream& os, const Stack& stack) {
    Node *current = stack.head;
    while (current != nullptr) { // iterate over stack
        if (current->getPayload().getOperator() != '\0') { // if node contains operator
            os << current->getPayload().getOperator(); // print operator
        } else {
            os << current->getPayload().getOperand(); // print operand
        }
        if (current->getNext() != nullptr)
            os << ", "; // print comma if more nodes
        current = current->getNext(); // move to next node
    }
    return os; // return stream
}

// Overloaded << operator for pushing to the stack
Stack& Stack::operator<<(Node* node) {
    node->setNext(head); // set next to head
    head = node; // set head to point at new node
    return *this; // return stack
}

// Overloaded >> operator for popping from the stack
Stack& Stack::operator>>(Node*& node) {
    if (head != nullptr) { // check that not empty
        node = head; // set ptr to head
        head = head->getNext(); // set head to point at new node
        node->setNext(nullptr);  // detach node from stack
    } else {
        node = nullptr; // if stack is empty, set node ptr to null
    }
    return *this; // return stack
}

// Destructor to recursively delete linked list
Stack::~Stack() {
    deleteNodesRecursively(head); // call helper function
}

// Recursive deletion helper
void Stack::deleteNodesRecursively(Node* node) {
    if (node != nullptr) { // check if not null
        deleteNodesRecursively(node->getNext()); // recursively call for next node
        delete node; // delete current node
    }
}
