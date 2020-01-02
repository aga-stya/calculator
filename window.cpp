#include "window.h"

#include <QPushButton>
#include <QSignalMapper>
#include <QGridLayout>
#include "CalculateResult.h"

Window::Window(QWidget *parent) : QWidget (parent), inputIsDouble(false)
{
    setFixedSize (400,600);

    outputBox = new QLabel(this);
    outputBox->setGeometry(0,0,400,100);
    QFont outputBoxFont("Times", 25, QFont::Bold);
    outputBox->setFont(outputBoxFont);
    outputBox->setNum(0);

    QGridLayout *gridLayout = new QGridLayout(this);

    for (int i=0; i<20; i++)
    {
        qDebug() << buttonNames[i] << " " << ((i/4)+1) << "," << (i%4);

        //Based on locale, change the decimal point representation to "," or "."
        if (buttonNames[i] == ",")
        {
            QLocale locale;
            if (locale.country() == QLocale::UnitedStates)
            {
                qDebug() << "country is us :" << locale.country();
                buttonNames[i] = ".";
            }
            else if (locale.country() == QLocale::Germany)
            {
                qDebug() << "country is germany :" << locale.country();
                buttonNames[i] = ",";
            }
            else
            {
                qDebug() << "default case :" << locale.country();
                buttonNames[i] = ",";
            }
        }
        buttons[i] = new QPushButton(buttonNames[i]);
        gridLayout->addWidget(buttons[i], ((i/4)+1), (i%4));
        //connect the buttons' clicked() signal to the slot buttonPressed()
        connect (buttons[i], SIGNAL(clicked()), this, SLOT(buttonPressed()));
    }
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0,0,0,0);
    setLayout(gridLayout);
}

void Window::clearEverything()
{
    inputIsDouble = false;
    outputBox->setText("0");
    operand1.str(std::string());
    qDebug() << QString::fromStdString(operand1.str());
}

void Window::buttonPressed()
{
    //Get the sender object
    QObject *obj = sender();

    //Cast it to the type PushButton
    QPushButton *pb = qobject_cast<QPushButton*>(obj);

    //get the text of the button which is also the value
    processNumbersPressed(pb->text());
}

void Window::processNumbersPressed(QString num)
{
    qDebug() << "Number pressed :" << num;
    if (num == "AC")
    {
        clearEverything();
    }
    else if (num == "=")
    {
        calculateResult();
    }
    else if (num == "," || num == ".")
    {
        qDebug() << ". is pressed";
        inputIsDouble = true;
        operand1 << num.toStdString();
        qDebug() << "concatenated string :" << QString::fromStdString(operand1.str());
        outputBox->setText(QString::fromStdString(operand1.str()));
    }
    else
    {
        operand1 << num.toStdString();
        qDebug() << "concatenated string :" << QString::fromStdString(operand1.str());
        outputBox->setText(QString::fromStdString(operand1.str()));
    }
}

void Window::calculateResult()
{
    qDebug() << "Calculate result function called";
    std::string result = "0";

    //Calculate the output of the expression using CalculateResult class
    CalculateResult res(operand1.str());
    result = res.result(inputIsDouble);
    outputBox->setText(QString::fromStdString(result));

    //operand1 set to the latest result
    operand1.str(result);
    inputIsDouble = false;
}

Window::~Window()
{

}
