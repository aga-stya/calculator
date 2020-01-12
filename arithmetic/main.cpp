#include "operation.hpp"
#include "calculator_multiplication.hpp"
#include "calculator_division.hpp"

#include <iostream>

int main()
{
    Operation *a = new Division("58", "32");
    std::cout << a->calculate_result() << std::endl;

}