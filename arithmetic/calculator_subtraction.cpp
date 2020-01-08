#include <string>
#include <algorithm>

#include "calculator_subtraction.hpp"

/*************************************************************************************************/

Subtraction::Subtraction(std::string oprnd1, std::string oprnd2)
            : borrow(0),
              minusSign(false),
              operand1(oprnd1),
              operand2(oprnd2)
{

}

/*************************************************************************************************/

bool Subtraction::checkIndividualParts (const std::string &firstPart, const std::string &secondPart)
{
    if (firstPart.size() > secondPart.size())
    {
        return true;
    }
    else if (secondPart.size() > firstPart.size())
    {
        minusSign = true;
        return false;
    }
    else if (firstPart.size() == secondPart.size())
    {
        int it = 0;
        while (it < (int)firstPart.size())
        {
            if (firstPart[it] > secondPart[it])
            {
                return true;
            }
            else if (secondPart[it] > firstPart[it])
            {
                minusSign = true;
                return false;
            }
            else if (firstPart[it] == secondPart[it])
            {
                it--;
            }
        }
    }
    //it should in any case not reach here
    std::cout << "control reaching here \n";
    return true;
}

/*************************************************************************************************/

void Subtraction::swapOperands(std::string &operand1, std::string &operand2)
{
    std::string operand1FractionalPart;
    std::string operand1IntegralPart;
    std::string operand2FractionalPart;
    std::string operand2IntegralPart;

    size_t found = std::string::npos;

    found = operand1.find(".");

    //if one does not have, then the other also does not have the decimal point
    if (found != std::string::npos)
    {
        operand1FractionalPart = operand1.substr(found+1, (operand1.size()-(found+1)));
        operand2FractionalPart = operand2.substr(found+1, (operand2.size()-(found+1)));
    }
    operand1IntegralPart = operand1.substr(0, found);
    operand2IntegralPart = operand2.substr(0, found);

    //check which is greater in the integral parts, if they are same check the fractional parts
    //case when the operand1's integral part is equal to operand2's integral part
    if (operand1IntegralPart == operand2IntegralPart)
    {
        //if no decimal point then no need to check for the fractional part
        if (found != std::string::npos)
        {
            // checkIndividualParts returns false when operand2FractionalPart is greater than operand1FractionalPart
            if (!checkIndividualParts(operand1FractionalPart, operand2FractionalPart))
            {
                std::string temp;
                temp = operand1;
                operand1 = operand2;
                operand2 = temp;
            }
            //else case is not required since we dont need to swap if operand1 is greater than operand2
        }
        return;
    }
    //case when the operand1's integral part is greater than operand2's integral part
    if (checkIndividualParts(operand1IntegralPart, operand2IntegralPart))
    {
        if (found != std::string::npos)
        {
            // checkIndividualParts returns false when operand2FractionalPart is greater than operand1FractionalPart
            if (!checkIndividualParts(operand1FractionalPart, operand2FractionalPart))
            {
                std::string temp;
                temp = operand1;
                operand1 = operand2;
                operand2 = temp;
            }
            //else case is not required since we dont need to swap if operand1 is greater than operand2
        }
    }
    else 
    {
        std::string temp;
        temp = operand1;
        operand1 = operand2;
        operand2 = temp;
    }
}

/*************************************************************************************************/

std::string Subtraction::singleDigitSubtraction (std::string operand1, std::string operand2)
{
    std::string difference = "0";
    std::string partial_difference = "0";

    if (operand1 == "." && operand2 == ".")
    {
        return ".";
    }

    //if there is a borrow, subtract one from operand1
    //if operand1 is "0", set the operand1 to "9", postpone the subtraction to later stages
    if (borrow > 0)
    {
        if (operand1 == "0")
        {
            operand1 = "9";
        }
        else
        {
            operand1 = std::to_string(stoi(operand1)-borrow);
            borrow = 0;
        }
    }
    //when operand1 is less than operand2, add 10 to it and then subtract, borrow is set to one
    if (operand1[0] < operand2[0])
    {
        borrow = 1;
        return std::to_string((stoi(operand1)+10) - stoi(operand2));
    }
    else 
    {
        return std::to_string((stoi(operand1)) - stoi(operand2));
    }
}

/*************************************************************************************************/

std::string Subtraction::calculate_result()
{
    std::string duplicate_operand1 = operand1;
    std::string duplicate_operand2 = operand2;

    //make both the operands of same size to make it simpler
    makeOperatorSizeEqual(duplicate_operand1, duplicate_operand2);

    //if both the operands are same then return 0 
    if (duplicate_operand1 == duplicate_operand2)
    {
        return "0";
    }

    //swapOperands will not handle the case of equal operands
    swapOperands (duplicate_operand1, duplicate_operand2);

    //subtraction starts here
    int it = duplicate_operand1.size() - 1;
    std::string result{""};

    //take individiual digits, do subtraction, take borrow if necessary (indicated by private member borrow)
    while (it >= 0)
    {
        //std::cout << "it :" << it << "\n";
        result = result + singleDigitSubtraction(duplicate_operand1.substr(it,1), duplicate_operand2.substr(it,1));
        it--;
    }
    std::reverse (result.begin(), result.end());

    if (minusSign)
        return ("-" + result);
    else 
        return result;
}

/*************************************************************************************************/
