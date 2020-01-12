#include <string>
#include <algorithm>
#include "ttmath/ttmath.h"

#include "calculator_division.hpp"

// I am doing this using the TTMATH library
typedef ttmath::Big<TTMATH_BITS(64), TTMATH_BITS(128)> MyBig;

/*************************************************************************************************/

Division::Division(std::string oprnd1, std::string oprnd2)
                                : operand1(oprnd1),
                                  operand2(oprnd2)
{

}

/*************************************************************************************************/

std::string Division::calculate_result()
{
    //make a copy of operand1 and operand2 before calling makeOperatorSizeEqual, because makeOperatorSizeEqual 
    //alters the values of operand1 and operand2

    std::string duplicate_operand1 = operand1;
    std::string duplicate_operand2 = operand2;
    std::string result;

    MyBig operand1_mybig;
    MyBig operand2_mybig;

    // string to MyBig conversion
    if (operand1_mybig.FromString(operand1) != 0)
    {
        return "carry or division by zero";
    }

    if (operand2_mybig.FromString(operand2) != 0)
    {
        return "carry or division by zero";
    }

    if( !operand1_mybig.Div(operand2_mybig) )
    {
        //return the result in string
        operand1_mybig.ToString(result);
        return result;
    }
    else
        return "division by zero";

    return result;
}

/*************************************************************************************************/
