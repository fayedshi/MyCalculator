#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStack>
#include<mynode.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT;

public:
    QStack<MyNode*> operands;
    QStack<char> optrs;
    MyNode anyNode;
    Widget(QWidget *parent = nullptr);
    ~Widget();
    bool verifyExpression(QString);
    void parseAndCompute(QString);
    void computeAndPack(bool);



private slots:
    void on_btn0_clicked();
    void on_btn1_clicked();
    void on_btn2_clicked();
    void on_btn3_clicked();
    void on_btn4_clicked();
    void on_btn5_clicked();
    void on_btn6_clicked();
    void on_btn7_clicked();
    void on_btn8_clicked();
    void on_btn9_clicked();
    void on_btnLfBkt_clicked();
    void on_btnRgtBkt_clicked();
    void showText(QObject *btn);


    void on_btnAdd_clicked();

    void on_btnSub_clicked();

    void on_btnMult_clicked();

    void on_btnDivd_clicked();

    void on_btnEqual_clicked();

    void on_backBtn_clicked();

    void on_btnClear_clicked();

    void on_btnUndo_clicked();

private:
    Ui::Widget *ui;

};
#endif // WIDGET_H
