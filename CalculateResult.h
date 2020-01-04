#ifndef CALCULATERESULT_H
#define CALCULATERESULT_H

#include <string>
#include <memory>

#include "arithmetic/operation.hpp"

class CalculateResult
{
public:
    CalculateResult(const CalculateResult&) = delete;
    CalculateResult(CalculateResult&&) = delete;
    CalculateResult(std::string operand_value);
    std::string result(bool isInputDouble);
    ~CalculateResult();

private:
    std::string operandValue;
    std::string calculatedResult;
    //all the arithmetic operations are executed using this pointer
    std::unique_ptr<Operation> mathsOperation;
};

#endif // CALCULATERESULT_H
