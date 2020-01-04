#include <string>
#include <algorithm>

#include "calculator_addition.hpp"

//constructor
Addition::Addition(std::string oprnd1, std::string oprnd2)
            : carry(0),
              Operation(oprnd1, oprnd2)
{

}

std::string Addition::singleDigitAddition (std::string operand1, std::string operand2)
{
    std::string sum = "0";
    std::string partial_sum = "0";
    std::cout << operand1 << "+" << operand2 <<"\n";

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


//std::string Addition::calculate_result(std::string operand1, std::string operand2)
std::string Addition::calculate_result()
{
    std::cout << "before changing sizes\n";
    std::cout << "operand1 :" << operand1 << "\n";
    std::cout << "operand2 :" << operand2 << "\n";

    //make both the operands of same size to make it simpler
    makeOperatorSizeEqual();

    std::cout << "after changing sizes\n";
    std::cout << "operand1 :" << operand1 << "\n";
    std::cout << "operand2 :" << operand2 << "\n";

    std::string result{""};

    //iterator for operands
    int it=(operand1.size()-1);

    //add each digit, append the result to the result variable
    while (it >= 0)
    {
        result = result + singleDigitAddition(operand1.substr(it,1), operand2.substr(it,1));
        it--;
    }

    //reverse the result
    std::reverse(result.begin(),result.end());
    
    if (carry > 0)
        result = std::to_string(carry) + result;
    return result;
}