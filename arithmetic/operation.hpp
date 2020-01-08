#ifndef OPERATION_HPP
#define OPERATION_HPP

#include <string>

//Interface for all the arithmetic operations
class Operation
{
    protected:
        //std::string operand1;
        //std::string operand2;
    public:
        //constructor
        Operation() = default;
        //calculate and return the addition result
        virtual std::string calculate_result() = 0;
        //virtual destructor
        virtual ~Operation(){};

    protected:
        //Following functions are used to format the operands
        //if the operands are of different sizes, then this method is used to make them of the same size
        void makeOperatorSizeEqual(std::string &operand1, std::string &operand2);
        //adds the necessary zeros to make the sizes equal
        void formatOperands(std::string &operand1, std::string &operand2);
        //used to check if a decimal point is present in an operand or not
        bool isOperandDouble (std::string &operand);
        //helper function
        void addZeros (std::string &val1, std::string &val2, bool integral_value = true);
};
#endif
