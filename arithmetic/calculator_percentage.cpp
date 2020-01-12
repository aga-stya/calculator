#include <string>
#include <algorithm>

#include "calculator_division.hpp"
#include "calculator_percentage.hpp"

/*************************************************************************************************/

Percentage::Percentage(std::string oprnd1)
                                : operand1(oprnd1)
{

}

/*************************************************************************************************/

std::string Percentage::calculate_result()
{
    std::string result;
    Division d(operand1, "100");
    result = d.calculate_result();
    return result;
}

/*************************************************************************************************/
