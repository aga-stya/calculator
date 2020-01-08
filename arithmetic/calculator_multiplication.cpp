#include <string>
#include <vector>
#include <algorithm>

#include "calculator_addition.hpp"
#include "calculator_multiplication.hpp"

/*************************************************************************************************/

Multiplication::Multiplication(std::string oprnd1, std::string oprnd2)
                                : carry(0),
                                operand1(oprnd1),
                                operand2(oprnd2)
{
    bool operand1_minus = false;
    bool operand2_minus = false;

    if (operand1[0] == '-')
    {
        operand1_minus = true;
        operand1 = operand1.substr(1,operand1.size());
    }
    if (operand2[0] == '-')
    {
        operand2_minus = true;
        operand2 = operand2.substr(1,operand2.size());
    }
    if (operand1_minus && operand2_minus)
    {
        minus = false;
    }
    else if (operand1_minus || operand2_minus)
    {
        minus = true;
    }

    int operand1PointPosition = 0;
    int operand2PointPosition = 0;

    operand1PointPosition = operand1.find('.');
    if (operand1PointPosition != std::string::npos)
    {
        operand1PointPosition = operand1.size() - 1 - operand1PointPosition;
        std::cout << "operand1 point position :" << operand1PointPosition << "\n";
        operand1.erase (operand1.find('.'), 1);
    }
    else 
    {
        operand1PointPosition = 0;
    }

    operand2PointPosition = operand2.find('.');
    if (operand2PointPosition != std::string::npos)
    {
        operand2PointPosition = operand2.size() - 1 - operand2PointPosition;
        std::cout << "operand2 point position :" << operand2PointPosition << "\n";
        operand2.erase (operand2.find('.'), 1);
    }
    else
    {
        operand2PointPosition = 0;
    }
    
    decimalPointPosition = operand1PointPosition + operand2PointPosition;
    std::cout << "decimal point position :" << decimalPointPosition << std::endl;
    std::cout << "after erase :" << operand1 << " , " << operand2 << std::endl;
}

/*************************************************************************************************/

std::string Multiplication::singleDigitMultiplication (char val1, char val2)
{
    int res_int = (val1 - '0') * (val2 - '0') + carry;
    carry = res_int/10;
    //std::cout << "carry :" << carry << ", " << "result :" << (res_int%10) << std::endl;
    return std::to_string(res_int%10);
}

/*************************************************************************************************/

void Multiplication::addDecimalPoint(std::string &result)
{
    if (decimalPointPosition != 0)
        result.insert((result.size() - decimalPointPosition), 1, '.');
    
}

/*************************************************************************************************/

std::string Multiplication::calculate_result()
{
    //make a copy of operand1 and operand2 before calling makeOperatorSizeEqual, because makeOperatorSizeEqual 
    //alters the values of operand1 and operand2

    std::string duplicate_operand1 = operand1;
    std::string duplicate_operand2 = operand2;

    std::cout << "before changing sizes\n";
    std::cout << "operand1 :" << duplicate_operand1 << "\n";
    std::cout << "operand2 :" << duplicate_operand2 << "\n";

    std::vector<std::string> partial_products;

    //iterator for operands
    int it=(duplicate_operand1.size()-1);
    int counterForZeros = 0;

    //outer loop for operand1
    for (auto it1 = duplicate_operand1.rbegin(); it1 != duplicate_operand1.rend(); it1++)
    {
        std::string temp_product;
        //reset carry
        carry = 0;
        //inner loop for operand2
        for (auto it2 = duplicate_operand2.rbegin(); it2 != duplicate_operand2.rend(); it2++)
        {
            //std::cout << *it1 << "*" << *it2 << std::endl;
            temp_product = temp_product + singleDigitMultiplication(*it1, *it2);
        }

        std::reverse (temp_product.begin(), temp_product.end());
        //append the carry in case of the multiplication of the last digit
        if (carry > 0)
        {
            temp_product = std::to_string(carry) + temp_product;
        }

        partial_products.push_back(temp_product + std::string(counterForZeros, '0'));
        std::cout << "partial product :" << temp_product + std::string(counterForZeros, '0') << std::endl;
        counterForZeros++;
    }

    //Add all the partial products to get the final product (without sign and decimal point)
    //Try to optimize this part by merging it into the inner loop of the above for loops
    std::string result{""};
    for (auto eachPartialProduct : partial_products)
    {
        Operation *a = new Addition (result, eachPartialProduct);
        result = a->calculate_result();
        delete a;
    }

    //Add sign to the result
    if (minus)
    {
        result = "-" + result;
    }

    //Add decimal point to the result
    addDecimalPoint(result);

    std::cout << "ouput of the operation is :" << operand1 << "+" << operand2 << "=" << result << std::endl;
    return result;
}

/*************************************************************************************************/
