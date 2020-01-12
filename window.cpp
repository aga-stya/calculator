#include "window.h"

#include <QPushButton>
#include <QSignalMapper>
#include <QGridLayout>
#include "CalculateResult.h"

Window::Window(QWidget *parent) : QWidget (parent), inputIsDouble(false), resultWasJustCalculated(false)
{
    //set default locale to avoid the problem with , and . for decimal point
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

    setFixedSize (400,600);

    QGridLayout *gridLayout = new QGridLayout(this);

    outputBox = new QLabel(this);
    outputBox->setFixedSize(400,100);
    QFont outputBoxFont("Times", 25, QFont::Bold);
    outputBox->setFont(outputBoxFont);
    outputBox->setNum(0);
    gridLayout->addWidget(outputBox,0,0);

    QFont buttonsFont("Calibre", 20, QFont::Thin);
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

//        if (buttonNames[i] == "AC")
//            buttons[i]->setFixedSize(200,100);
//        else
//            buttons[i]->setFixedSize(100,100);
        buttons[i]->setFixedSize(100,100);
        buttons[i]->setFont(buttonsFont);
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

void Window::newValueToTextBox (std::string text)
{
    operand1.str(std::string());
    operand1 << text;
    outputBox->setText(QString::fromStdString(text));
}

void Window::appendValueToTextBox (std::string text)
{
    QString textInBox = outputBox->text();

    if (textInBox == "0")
        textInBox = "";
    std::string temp;
    temp = textInBox.toStdString() + text;
    operand1.str(std::string());
    operand1 << temp;

    textInBox = QString::fromStdString(temp);
    outputBox->setText(textInBox);
}

void Window::clearLastCharacter ()
{
    QString textInBox = outputBox->text();

    if (textInBox.length() == 1)
    {
        newValueToTextBox ("0");
    }
    else
    {
        std::string temp;
        temp = textInBox.toStdString();
        temp = temp.substr(0, (temp.size() - 1));
        newValueToTextBox(temp);
    }
}

bool Window::canCallCalculateResult()
{
    std::string temp = operand1.str();
    if (temp.size() > 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Window::processNumbersPressed(QString num)
{
    qDebug() << "Number pressed :" << num;

    if (num == "about")
    {
        QApplication::aboutQt();
    }
    //clear everything in the textbox and replace it by 0
    else if (num == "AC")
    {
        clearEverything();
    }
    //clear only the last character
    else if (num == "clear")
    {
        clearLastCharacter();
    }
    //check if the button pressed is a number
    else if (num[0] >= 48 && num[0] <= 57)
    {
        //add a * symbol when no other sign is pressed after the % calculation
        if (percentageResultCalculated)
        {
            appendValueToTextBox("*");
            percentageResultCalculated = false;
        }

        //If the result was just calculated, clear the values in the box else append to the values in the box
        if (resultWasJustCalculated)
        {
            newValueToTextBox(num.toStdString());
            resultWasJustCalculated = false;
        }
        else
        {
            appendValueToTextBox (num.toStdString());
        }

    }
    else if (num == "%")
    {
        //calculate the result if only one operand is available
        appendValueToTextBox (num.toStdString());
        if (calculateResult())
            percentageResultCalculated = true;
    }
    else if (num == "+" ||
             num == "-" ||
             num == "*" ||
             num == "/" )
    {
        //after pressing the symbols, the result is not recent
        resultWasJustCalculated = false;

        //This is to avoid adding an automatic "*" after the calculation of the percentage
        if (percentageResultCalculated)
        {
            percentageResultCalculated = false;
        }

        if (canCallCalculateResult())
        {
            //If the calculateResult() does not return the same value as the operand, it means that the result was calculated
            if (calculateResult())
            {
                resultWasJustCalculated = true;
            }
            else
            {
                resultWasJustCalculated = false;
            }
        }
        appendValueToTextBox(num.toStdString());
    }
    else if (num == "=")
    {
        if (calculateResult())
            resultWasJustCalculated = true;
    }
    else if (num == "," || num == ".")
    {
        //if the result was recently calculated, do not accept the .
        if (!resultWasJustCalculated)
        {
            inputIsDouble = true;
            //resultWasJustCalculated = false;
            appendValueToTextBox(num.toStdString());
        }
    }
}

//format the result before displaying the result
void formatResult (std::string &result)
{
    if (result[result.size()-1] == '.')
    {
        result = result + "00";
    }
}

bool Window::calculateResult()
{
    qDebug() << "Calculate result function called";

    std::string result = "0";
    qDebug() << "operand1 :" << QString::fromStdString(operand1.str());

    //Calculate the output of the expression using CalculateResult class
    CalculateResult res(operand1.str());
    result = res.result();
    qDebug() << "result calculated :" << QString::fromStdString(result);
    //to make sure that the result calculation was successful
    bool retval = true;
    if (result == operand1.str())
        retval = false;

    //format the result before displaying the result
    formatResult (result);

    //add the value to the text box
    newValueToTextBox(result);
    inputIsDouble = false;

    return retval;
}

Window::~Window()
{

}
