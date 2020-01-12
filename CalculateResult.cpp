#include "CalculateResult.h"
#include <QDebug>
#include <QString>
#include <memory>
#include <exception>

#include "arithmetic/operation.hpp"
#include "arithmetic/calculator_addition.hpp"
#include "arithmetic/calculator_subtraction.hpp"
#include "arithmetic/calculator_multiplication.hpp"
#include "arithmetic/calculator_division.hpp"
#include "arithmetic/ttmath/ttmath.h"

CalculateResult::CalculateResult(std::string operand_value) : operandValue(operand_value)
{
    qDebug() << "CalculateResult constructor, operand :" << QString::fromStdString(operand_value);
}

std::string CalculateResult::result()
{
    try {
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
            mathsOperation = std::make_unique<Division> (operandValue.substr(0, (found)).c_str(), operandValue.substr(found+1, operandValue.size()).c_str());
            return mathsOperation->calculate_result();
        }

        found = operandValue.find('%');

        if (found != std::string::npos)
        {
            qDebug() << "Percentage operation";
            mathsOperation = std::make_unique<Division> (operandValue.substr(0, (found)).c_str(), "100");
            return mathsOperation->calculate_result();
        }

        //+/- still needs to be implemented
        return operandValue;
    }
    catch(std::exception &e){
        qDebug() << "Error while performing the operation :" << e.what();
        return operandValue;
    }
}

CalculateResult::~CalculateResult()
{

}
