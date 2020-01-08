#ifndef CALCULATOR_MULTIPLICATION_HPP
#define CALCULATOR_MULTIPLICATION_HPP

#include <iostream>
#include "operation.hpp"

class Multiplication : public Operation
{
    public:
        //only one constructor
        Multiplication(std::string oprnd1, std::string oprnd2);
        //no copy constructor
        Multiplication(const Multiplication&) = delete;
        //no move constructor
        Multiplication(Multiplication &&) = delete;
        //no copy assignment
        Multiplication& operator=(const Multiplication&) = delete;

        //calculate and return the addition result
        virtual std::string calculate_result();

        //performs addition on single digits
        std::string singleDigitMultiplication (char val1, char val2);

        //append the output of each singleDigitMultiplication to the result
        void appendResult(std::string, std::string&);

        //calculate the final decimal position
        void addDecimalPoint(std::string &result);
        //use the default constructor
        //~Addition();

    private:
        unsigned int carry;
        std::string operand1;
        std::string operand2;
        bool minus;
        int decimalPointPosition;
};

#endif