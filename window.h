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
                                ",",
                                "=",
                               " "};

    QPushButton *buttons[20];

    QLabel *outputBox;

    std::stringstream operand1;
    bool inputIsDouble;
};
#endif // WINDOW_H
