#ifndef CALCULATERESULT_H
#define CALCULATERESULT_H

#include <string>

class CalculateResult
{
public:
    CalculateResult(const CalculateResult&) = delete;
    CalculateResult(CalculateResult&&) = delete;
    CalculateResult(std::string operand_value);
    ~CalculateResult();
    std::string result();

private:
    std::string operandValue;
    std::string calculatedResult;
};

#endif // CALCULATERESULT_H
