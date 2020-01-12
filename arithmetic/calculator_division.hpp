#ifndef CALCULATOR_DIVISION_HPP
#define CALCULATOR_DIVISION_HPP

#include <iostream>
#include "operation.hpp"

class Division : public Operation
{
    public:
        //only one constructor
        Division(std::string oprnd1, std::string oprnd2);
        //no copy constructor
        Division(const Division&) = delete;
        //no move constructor
        Division(Division &&) = delete;
        //no copy assignment
        Division& operator=(const Division&) = delete;

        //calculate and return the division result
        virtual std::string calculate_result();

        //use the default destructor
        //~Division();

    private:
        std::string operand1;
        std::string operand2;
};

#endif