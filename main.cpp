// Project 4
// Naomi Shah nns220002
// main.cpp

#include "Stack.h"
#include "Node.h"
#include "Data.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <cctype>
#include <iomanip>

using namespace std;

// Function to determine the precedence of operators
int precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default:  return 0;
    }
}

// Function to check if a string is int or float
bool isOperand(const string& token) {
    stringstream ss(token);
    double value;
    // Extract a double from ss
    if (ss >> value) {
        // If successful, it's a valid operand
        return true;
    } else {
        // Not a valid operand
        return false;
    }
}

// Function to check if a character is an operator
bool isOperator(char c) {
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        return true;
    }
    return false;
}

// Function to convert an infix to a postfix expression
string convertToPostfix(const string& infix) {
    Stack opStack; // stack to hold operators
    string postfix = "";
    bool lastWasOperand = false;  // handles spaces

    stringstream ss(infix);
    string token;
    while (ss >> token) {
        for (char c : token) { // iterates over chars in token
            if (isdigit(c) || c == '.') {  // handles digit/decimal point
                postfix += c; // append to postfix
                lastWasOperand = true;
            } else { // handle operator
                if (lastWasOperand) {
                    postfix += ' ';  // add space after operand
                    lastWasOperand = false;
                }
                if (c == '(') { // handle opening parenthesis
                    opStack << new Node(Data(0, c)); // push ( with default operand/operator
                } else if (c == ')') { // handle close parenthesis
                    Node* tempNode = nullptr; // node holder
                    while (opStack.getHead() && opStack.getHead()->getPayload().getOperator() != '(') {
                        opStack >> tempNode; // pop operators until (
                        postfix += tempNode->getPayload().getOperator(); // append operator
                        postfix += ' '; // add space
                        delete tempNode; // free mem
                    }
                    opStack >> tempNode;  // pop (
                    delete tempNode; // free mem
                } else if (&isOperator) { // handles other operators
                    while (opStack.getHead() && precedence(c) <= precedence(opStack.getHead()->getPayload().getOperator())) {
                        Node* tempNode = nullptr;
                        opStack >> tempNode; // pop operators with >= precedence
                        postfix += tempNode->getPayload().getOperator(); // append operator
                        postfix += ' '; // add space
                        delete tempNode; // free mem
                    }
                    opStack << new Node(Data(0, c)); // push operator with default operand
                }
            }
        }
    }
    while (opStack.getHead()) { // handle remaining operators
        Node* tempNode = nullptr;
        opStack >> tempNode; // pop remaining operators
        postfix += ' '; // add space BEFORE operator
        postfix += tempNode->getPayload().getOperator(); // append operator
        delete tempNode; // free mem
    }
    return postfix;
}

// Function to evaluate a postfix expression
double evaluatePostfix(const string& postfix) {
    istringstream iss(postfix);
    string token; // expression holder
    Stack valStack; // stack to hold operands
    while (iss >> token) {
        if (isdigit(token[0]) || token.find('.') != string::npos) { // check if operand
            valStack << new Node(Data(stod(token), '\0')); // push operand
        } else { // operator
            Node* rightNode = nullptr, *leftNode = nullptr;
            valStack >> rightNode; // pop right operand
            double right = rightNode->getPayload().getOperand(); // get operand value
            delete rightNode; // free mem
            valStack >> leftNode; // pop left operand
            double left = leftNode->getPayload().getOperand(); // get operand value
            delete leftNode; // free mem
            double result = 0;
            switch (token[0]) { // perform operation
                case '+': result = left + right; break;
                case '-': result = left - right; break;
                case '*': result = left * right; break;
                case '/': result = left / right; break;
                case '^': result = pow(left, right); break;
            }
            valStack << new Node(Data(result, '\0')); // push result back onto stack
        }
    }
    Node* resultNode = nullptr;
    valStack >> resultNode; // pop final result
    double finalResult = resultNode->getPayload().getOperand(); // get result value
    delete resultNode; // free mem
    return finalResult;
}
    
    int main() {
        // Get filename from user
        string filename;
        cout << "Enter filename: ";
        cin >> filename;

        // Check if valid opening
        ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return 1;
        }
            
        string expression;
        while (getline(inputFile, expression)) { // read expression from file
            if (expression.empty()) continue; // skip empty lines
            string postfix = convertToPostfix(expression); // convert infix expression to postfix
            double result = evaluatePostfix(postfix); // evaluate postfix expressionc
            cout << postfix << "\t" << fixed << setprecision(3) << result << endl;
        }

        inputFile.close();
        
        return 0;
    }

