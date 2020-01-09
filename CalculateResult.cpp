#include "CalculateResult.h"
#include <QDebug>
#include <QString>
#include <memory>

#include "arithmetic/operation.hpp"
#include "arithmetic/calculator_addition.hpp"
#include "arithmetic/calculator_subtraction.hpp"
#include "arithmetic/calculator_multiplication.hpp"

CalculateResult::CalculateResult(std::string operand_value) : operandValue(operand_value)
{
    qDebug() << "CalculateResult constructor, operand :" << QString::fromStdString(operand_value);
}

std::string CalculateResult::result(bool isInputDouble)
{
    size_t found = operandValue.find('+');

    if (found != std::string::npos)
    {
        qDebug() << "addition operation";
        mathsOperation = std::make_unique<Addition> (operandValue.substr(0, (found)).c_str(), operandValue.substr(found+1, operandValue.size()).c_str());
        return mathsOperation->calculate_result();
    }

    found = operandValue.find('*');
    if (found != std::string::npos)
    {
        qDebug() << "Multiplication operation";
        mathsOperation = std::make_unique<Multiplication> (operandValue.substr(0, (found)).c_str(), operandValue.substr(found+1, operandValue.size()).c_str());
        return mathsOperation->calculate_result();
    }

    found = operandValue.find('-');
    if (found != std::string::npos)
    {
        qDebug() << "subtraction operation";
        mathsOperation = std::make_unique<Subtraction> (operandValue.substr(0, (found)).c_str(), operandValue.substr(found+1, operandValue.size()).c_str());
        return mathsOperation->calculate_result();
    }

    found = operandValue.find('/');
    if (found != std::string::npos)
    {
        qDebug() << "Division operation";
        if (isInputDouble)
        {
            qDebug() << "operands have double in them";
            double oper1 = 0.0;
            double oper2 = 0.0;
            oper1 = std::stod(operandValue.substr(0, (found)).c_str());
            oper2 = std::stod(operandValue.substr(found+1, operandValue.size()).c_str());

            if (oper2 == 0)
            {
                calculatedResult = "Can't divide by 0";
                return calculatedResult;
            }
            calculatedResult = std::to_string(oper1 / oper2);
            qDebug() << QString::fromStdString(calculatedResult);
            return calculatedResult;
        }
        else
        {
            qDebug() << "operands have int in them";
            int oper1 = 0.0;
            int oper2 = 0.0;
            oper1 = std::stoi(operandValue.substr(0, (found)).c_str());
            oper2 = std::stoi(operandValue.substr(found+1, operandValue.size()).c_str());

            if (oper2 == 0)
            {
                calculatedResult = "Can't divide by 0";
                return calculatedResult;
            }

            calculatedResult = std::to_string(oper1 / oper2);
            qDebug() << QString::fromStdString(calculatedResult);
            return calculatedResult;
        }
    }

    //% and +/- still needs to be implemented
    return operandValue;
}

CalculateResult::~CalculateResult()
{

}
