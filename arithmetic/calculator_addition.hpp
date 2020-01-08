#ifndef CALCULATOR_ADDITION_HPP
#define CALCULATOR_ADDITION_HPP

#include <iostream>
#include "operation.hpp"

class Addition : public Operation
{
    public:
        //only one constructor
        Addition(std::string oprnd1, std::string oprnd2);
        //no copy constructor
        Addition(const Addition&) = delete;
        //no move constructor
        Addition(Addition &&) = delete;
        //no copy assignment
        Addition& operator=(const Addition&) = delete;

        //calculate and return the addition result
        virtual std::string calculate_result();

        //performs addition on single digits
        std::string singleDigitAddition (std::string operand1, std::string operand2);

        //use the default constructor
        //~Addition();

    private:
        unsigned int carry;
        std::string operand1;
        std::string operand2;
};

#endif