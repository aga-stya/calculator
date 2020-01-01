#include "CalculateResult.h"
#include <QDebug>

CalculateResult::CalculateResult(std::string operand_value)
{
    operandValue = operand_value;

    qDebug() << "CalculateResult constructor, operand :" << QString::fromStdString(operand_value);
    std::string operand1;
    std::string operand2;
    double oper1 = 0.0;
    double oper2 = 0.0;

    size_t found = operand_value.find('+');

    if (found != std::string::npos)
    {
        qDebug() << "addition found";
        operand1 = operandValue.substr(0, (found));
        operand2 = operandValue.substr(found+1, operandValue.size());
        qDebug() << "operand1 :" << QString::fromStdString(operand1);
        qDebug() << "operand2 :" << QString::fromStdString(operand2);
        oper1 = atof(operand1.c_str());
        oper2 = atof(operand2.c_str());
        calculatedResult = std::to_string(oper1 + oper2);
    }
    else
    {
        qDebug() << "addition not found";
    }

    found = operand_value.find('-');
    if (found != std::string::npos)
    {
        qDebug() << "subtraction found";
        operand1 = operandValue.substr(0, (found));
        operand2 = operandValue.substr(found+1, operandValue.size());
        qDebug() << "operand1 :" << QString::fromStdString(operand1);
        qDebug() << "operand2 :" << QString::fromStdString(operand2);
        oper1 = atof(operand1.c_str());
        oper2 = atof(operand2.c_str());
        calculatedResult = std::to_string(oper1 - oper2);
    }
    else
    {
        qDebug() << "subtraction not found";
    }

    found = operand_value.find('*');
    if (found != std::string::npos)
    {
        qDebug() << "multiplication found";
        operand1 = operandValue.substr(0, (found));
        operand2 = operandValue.substr(found+1, operandValue.size());
        qDebug() << "operand1 :" << QString::fromStdString(operand1);
        qDebug() << "operand2 :" << QString::fromStdString(operand2);
        oper1 = atof(operand1.c_str());
        oper2 = atof(operand2.c_str());
        calculatedResult = std::to_string(oper1 * oper2);
    }
    else
    {
        qDebug() << "multiplication not found";
    }

    found = operand_value.find('/');
    if (found != std::string::npos)
    {
        qDebug() << "Division found";
        operand1 = operandValue.substr(0, (found));
        operand2 = operandValue.substr(found+1, operandValue.size());
        qDebug() << "operand1 :" << QString::fromStdString(operand1);
        qDebug() << "operand2 :" << QString::fromStdString(operand2);
        oper1 = atof(operand1.c_str());
        oper2 = atof(operand2.c_str());
        calculatedResult = std::to_string(oper1 / oper2);
    }
    else
    {
        qDebug() << "Division not found";
    }

    //% and +/- still needs to be implemented
}

std::string CalculateResult::result()
{
    return calculatedResult;
}

CalculateResult::~CalculateResult()
{

}
