#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStack>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void parseExpression(QString expr, QStack<int> *oprnds, QStack<char> *optrs);
    int consumeStacks(QStack<int> *operands, QStack<char> *optrs);
    int compute(char optr,int lOprnd, int rOprnd);

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

private:
    Ui::Widget *ui;

};
#endif // WIDGET_H
