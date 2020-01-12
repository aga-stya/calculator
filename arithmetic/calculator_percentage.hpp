#ifndef CALCULATOR_Percentage_HPP
#define CALCULATOR_Percentage_HPP

#include <iostream>
#include "operation.hpp"

class Percentage : public Operation
{
    public:
        //only one constructor
        Percentage(std::string oprnd1);
        //no copy constructor
        Percentage(const Percentage&) = delete;
        //no move constructor
        Percentage(Percentage &&) = delete;
        //no copy assignment
        Percentage& operator=(const Percentage&) = delete;

        //calculate and return the Percentage result
        virtual std::string calculate_result();

        //use the default destructor
        //~Percentage();

    private:
        std::string operand1;
};

#endif