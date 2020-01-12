#include <string>
#include <algorithm>
#include <iostream>

#include "operation.hpp"

//constructor

//checks for the decimal point in any of the operands
bool Operation::isOperandDouble (std::string &operand)
{
    if (operand.find(".") != std::string::npos)
    {
        return true;
    }
    return false;
}

//add the necessary zeros
void Operation::addZeros (std::string &val1, std::string &val2, bool integral_value)
{
    //std::cout << "addZeros," << "val1 :" << val1 << ", val2 :" << val2 << "\n";
    //operand1's size is bigger than operand2
    if (val2.size() < val1.size())
    {
        //std::cout << (val2.size()) << "\n";
        std::string tmp ((val1.size()-val2.size()), '0');
        //std::cout << "tmp :" << tmp << "\n";
        if (integral_value)
        {
            val2 = tmp + val2;
        }
        else
        {
            val2 = val2 + tmp;
        }
    }
    //operand2's size is bigger than operand1
    else if (val1.size() < val2.size())
    {
        //std::cout << val1.size() << "\n";
        std::string tmp ((val2.size()-val1.size()), '0');
        //std::cout << "tmp :" << tmp << "\n";
        if (integral_value)
        {
            val1 = tmp + val1;
        }
        else
        {
            val1 = val1 + tmp;
        }
    }
    //std::cout << "end of addZeros," << "val1 :" << val1 << ", val2 :" << val2 << "\n";
}

void Operation::formatOperands(std::string &operand1, std::string &operand2)
{
    std::string operand1_integral_part;
    std::string operand1_fractional_part;
    std::string operand2_integral_part;
    std::string operand2_fractional_part;

    size_t found = operand1.find(".");
    if (found != std::string::npos)
    {
        operand1_integral_part = operand1.substr(0, found);
        operand1_fractional_part = operand1.substr(found+1, operand1.size());
        //std::cout << "operand1 :" << "integral :" << operand1_integral_part << " fractional :" << operand1_fractional_part << "\n";
    }

    found = operand2.find(".");
    if (found != std::string::npos)
    {
        operand2_integral_part = operand2.substr(0, found);
        operand2_fractional_part = operand2.substr(found+1, operand2.size());
        //std::cout << "operand2 :" << "integral :" << operand2_integral_part << " fractional :" << operand2_fractional_part << "\n";
    }

    //make the integral sizes equal
    addZeros (operand1_integral_part, operand2_integral_part, true);
    //make the integral sizes equal
    addZeros (operand1_fractional_part, operand2_fractional_part, false);

    //std::cout << "final results \n";
    operand1 = operand1_integral_part + "." + operand1_fractional_part;
    operand2 = operand2_integral_part + "." + operand2_fractional_part;
    //std::cout << operand1 << "\n";
    //std::cout << operand2 << "\n";
}

void Operation::makeOperatorSizeEqual(std::string &operand1, std::string &operand2)
{
    //operand1 has decimal point, operand2 has no decimal point
    if (isOperandDouble(operand1) && !isOperandDouble(operand2))
    {
        //add decimal point to operand2
        operand2 = std::to_string(stod(operand2));
        //std::cout << "adding decimal point to operand2 :" << operand2 << "\n";
        formatOperands (operand1, operand2);
    }
    //operand1 has no decimal point, operand2 has decimal point
    else if (!isOperandDouble(operand1) && isOperandDouble(operand2))
    {
        //add decimal point to operand1
        operand1 = std::to_string(stod(operand1));
        //std::cout << "adding decimal point to operand1 :" << operand1 << "\n";
        formatOperands (operand1, operand2);
    }
    //both operands have decimal point
    else if (isOperandDouble(operand1) && isOperandDouble(operand2))
    {
        formatOperands (operand1, operand2);
    }
    //both operands have no decimal point
    else if (!isOperandDouble(operand1) && !isOperandDouble(operand2))
    {
        //operand1's size is bigger than operand2
        addZeros (operand1, operand2, true);
    }
}  
