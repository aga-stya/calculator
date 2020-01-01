#ifndef WINDOW_H
#define WINDOW_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <string>
#include <sstream>

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    virtual ~Window();

private slots:

    void buttonPressed();
    void clearEverything();

private:
    //void processNumbersPressed(double num);
    void processNumbersPressed(QString num);
    void calculateResult();
private:
//    QPushButton *pb2;
//    QPushButton *pb3;
//    QPushButton *pb1;
//    QPushButton *pb4;
//    QPushButton *pb5;
//    QPushButton *pb6;
//    QPushButton *pb7;
//    QPushButton *pb8;
//    QPushButton *pb9;
//    QPushButton *pb0;
//    QPushButton *pbAC;
//    QPushButton *pbPlusMinus;
//    QPushButton *pbPercent;
//    QPushButton *pbDivide;
//    QPushButton *pbMultiply;
//    QPushButton *pbMinus;
//    QPushButton *pbPlus;
//    QPushButton *pbDot;
//    QPushButton *pbEqual;

    QStringList buttonNames = { "AC",
                                "+/-",
                                "%",
                                "/",
                                "7",
                                "8",
                                "9",
                                "*",
                                "4",
                                "5",
                                "6",
                                "-",
                                "1",
                                "2",
                                "3",
                                "+",
                                "0",
                                ".",
                                "=",
                               " "};

    QPushButton *buttons[20];

    QLabel *outputBox;

    std::stringstream operand1;
};
#endif // WINDOW_H
