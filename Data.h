//  Data.h

#ifndef DATA_H
#define DATA_H

class Data {
private:
    double Operand = 0.0;
    char Operator = '\0';
    
public:
    // Constructors
    Data(){}; // default
    Data(double op, char opr) {Operand = op; Operator = opr;} // overloaded
    
    // Accessors
    double getOperand() const {return Operand;}
    char getOperator() const {return Operator;}
    
    // Mutators
    void setOperand(double num) {Operand = num;}
    void setOperator(char sign) {Operator = sign;}
};

#endif
