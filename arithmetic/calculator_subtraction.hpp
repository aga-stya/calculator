#ifndef CALCULATOR_SUBTRACTION_HPP
#define CALCULATOR_SUBTRACTION_HPP

#include <iostream>
#include "operation.hpp"

class Subtraction : public Operation
{
    public:
        //only one constructor
        Subtraction(std::string oprnd1, std::string oprnd2);
        //no copy constructor
        Subtraction(const Subtraction&) = delete;
        //no move constructor
        Subtraction(Subtraction &&) = delete;
        //no copy assignment
        Subtraction& operator=(const Subtraction&) = delete;

        //calculate and return the Subtraction result
        virtual std::string calculate_result();
        //if operand1 is not greater than operand2, then swap the values in the operands
        void swapOperands(std::string &operand1, std::string &operand2);

        bool checkIndividualParts (const std::string &firstPart, const std::string &secondPart);
        std::string singleDigitSubtraction (std::string operand1, std::string operand2);

        //use the default constructor
        //~Subtraction();

    private:
        unsigned int borrow;
        bool minusSign;
};

#endif