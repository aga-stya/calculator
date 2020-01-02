#include "CalculateResult.h"
#include <QDebug>
#include <QString>

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

        if (isInputDouble)
        {
            qDebug() << "operands have double in them";
            double oper1 = 0.0;
            double oper2 = 0.0;
            oper1 = atof(operandValue.substr(0, (found)).c_str());
            oper2 = atof(operandValue.substr(found+1, operandValue.size()).c_str());
            qDebug() << "oper1 :" << oper1;
            qDebug() << "oper2 :" << oper2;
            calculatedResult = std::to_string(oper1 + oper2);
            return calculatedResult;
        }
        else
        {
            qDebug() << "operands have int in them";
            int oper1 = 0.0;
            int oper2 = 0.0;
            oper1 = std::stoi(operandValue.substr(0, (found)).c_str());
            oper2 = std::stoi(operandValue.substr(found+1, operandValue.size()).c_str());
            calculatedResult = std::to_string(oper1 + oper2);
            qDebug() << QString::fromStdString(calculatedResult);
            return calculatedResult;
        }
    }

    found = operandValue.find('-');
    if (found != std::string::npos)
    {
        qDebug() << "subtraction operation";
        if (isInputDouble)
        {
            qDebug() << "operands have double in them";
            double oper1 = 0.0;
            double oper2 = 0.0;
            oper1 = atof(operandValue.substr(0, (found)).c_str());
            oper2 = atof(operandValue.substr(found+1, operandValue.size()).c_str());
            calculatedResult = std::to_string(oper1 - oper2);
            return calculatedResult;
        }
        else
        {
            qDebug() << "operands have int in them";
            int oper1 = 0.0;
            int oper2 = 0.0;
            oper1 = std::stoi(operandValue.substr(0, (found)).c_str());
            oper2 = std::stoi(operandValue.substr(found+1, operandValue.size()).c_str());
            calculatedResult = std::to_string(oper1 - oper2);
            qDebug() << QString::fromStdString(calculatedResult);
            return calculatedResult;
        }
    }

    found = operandValue.find('*');
    if (found != std::string::npos)
    {
        qDebug() << "multiplication operation";
        if (isInputDouble)
        {
            qDebug() << "operands have double in them";
            double oper1 = 0.0;
            double oper2 = 0.0;
            oper1 = std::stod(operandValue.substr(0, (found)).c_str());
            oper2 = std::stod(operandValue.substr(found+1, operandValue.size()).c_str());
            calculatedResult = std::to_string(oper1 * oper2);
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
            calculatedResult = std::to_string(oper1 * oper2);
            qDebug() << QString::fromStdString(calculatedResult);
            return calculatedResult;
        }
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
