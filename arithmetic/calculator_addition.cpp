#include <string>
#include <algorithm>

#include "calculator_addition.hpp"

/*************************************************************************************************/

Addition::Addition(std::string oprnd1, std::string oprnd2)
                                : carry(0),
                                operand1(oprnd1),
                                operand2(oprnd2)
{

}

/*************************************************************************************************/

std::string Addition::singleDigitAddition (std::string operand1, std::string operand2)
{
    std::string sum = "0";
    std::string partial_sum = "0";
    //std::cout << operand1 << "+" << operand2 <<"\n";

    if (operand1 == "." && operand2 == ".")
    {
        return ".";
    }

    sum = std::to_string(stoi(operand1)+stoi(operand2)+carry);

    //If the size of the sum is 2 digits, then use the 2nd digit as carry, else carry is 0
    if (sum.size() > 1)
    {
        partial_sum = sum.substr(1,1);
        carry = stoi(sum.substr(0,1));
    }
    else
    {
        partial_sum = sum.substr(0,1);
        carry = 0;
    }
    
    //cout << "carry :" << carry << ";" << "partial_sum :" << partial_sum << "\n";
    return partial_sum;
}

/*************************************************************************************************/

std::string Addition::calculate_result()
{
    //make a copy of operand1 and operand2 before calling makeOperatorSizeEqual, because makeOperatorSizeEqual 
    //alters the values of operand1 and operand2

    std::string duplicate_operand1 = operand1;
    std::string duplicate_operand2 = operand2;

    //std::cout << "before changing sizes\n";
    //std::cout << "operand1 :" << duplicate_operand1 << "\n";
    //std::cout << "operand2 :" << duplicate_operand2 << "\n";

    //make both the operands of same size to make it simpler
    makeOperatorSizeEqual(duplicate_operand1, duplicate_operand2);

    //std::cout << "after changing sizes\n";
    //std::cout << "operand1 :" << duplicate_operand1 << "\n";
    //std::cout << "operand2 :" << duplicate_operand2 << "\n";

    std::string result{""};

    //iterator for operands
    int it=(duplicate_operand1.size()-1);

    //add each digit, append the result to the result variable
    while (it >= 0)
    {
        result = result + singleDigitAddition(duplicate_operand1.substr(it,1), duplicate_operand2.substr(it,1));
        it--;
    }

    //reverse the result
    std::reverse(result.begin(),result.end());
    
    if (carry > 0)
        result = std::to_string(carry) + result;

    std::cout << "ouput of the operation is :" << operand1 << "+" << operand2 << "=" << result << std::endl;
    return result;
}

/*************************************************************************************************/
