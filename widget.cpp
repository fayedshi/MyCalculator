#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
//    this->setMaximumSize(200,280);
//    this->setMinimumSize(200,280);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btn0_clicked()
{
    showText(ui->btn0);
}

void Widget::on_btn1_clicked()
{
    showText(ui->btn1);
}

void Widget::on_btn2_clicked()
{
    showText(ui->btn2);
}
void Widget::on_btn3_clicked()
{
    showText(ui->btn3);
}
void Widget::on_btn4_clicked()
{
    showText(ui->btn4);
}
void Widget::on_btn5_clicked()
{
    showText(ui->btn5);
}

void Widget::on_btn6_clicked()
{
    showText(ui->btn6);
}

void Widget::on_btn7_clicked()
{
    showText(ui->btn7);
}
void Widget::on_btn8_clicked()
{
    showText(ui->btn8);
}
void Widget::on_btn9_clicked()
{
    showText(ui->btn9);
}

void Widget::showText(QObject *btn){
    QPushButton *qBtn=qobject_cast<QPushButton *>(btn);
//    qDebug("here now");
    ui->lineEdit->setText(ui->lineEdit->text()+qBtn->text());
}

void Widget::on_btnLfBkt_clicked()
{
    showText(ui->btnLfBkt);
}

void Widget::on_btnRgtBkt_clicked()
{
    showText(ui->btnRgtBkt);
}


void Widget::on_btnAdd_clicked()
{
    showText(ui->btnAdd);
}


void Widget::on_btnSub_clicked()
{
    showText(ui->btnSub);
}


void Widget::on_btnMult_clicked()
{
    showText(ui->btnMult);
}


void Widget::on_btnDivd_clicked()
{
    showText(ui->btnDivd);
}


void Widget::on_btnEqual_clicked()
{
    QStack<int> operands;
    QStack<char> optrs;
    QString expr= ui->lineEdit->text();
    // todo: verify expression first
    // verifyExpression()
    parseExpression(expr,&operands,&optrs);
    // now operands stack and operators stack is loaded
    int result= computeRest(&operands,&optrs);
    ui->lineEdit->setText(QString::number(result));
}


int Widget:: computeRest(QStack<int> *operands, QStack<char> *optrs){
    while(!optrs->isEmpty()){
        operands->push(compute(optrs->pop(),operands->pop(), operands->pop()));
    }
    return operands->pop();
}

void Widget::parseExpression(QString expr, QStack<int> *operands, QStack<char> *optrs){
    int i=0, len=expr.length();
    while(i<len){
        QChar qch =expr.at(i);
        if(qch >='0' && qch <='9'){
            QString num;
            while(i< len && expr.at(i) >='0' && expr.at(i) <='9'){
                num.append(expr.at(i++));
            }
            i--;
            operands->push(num.toUInt());
            // execute for multiply or divide whenever met
            if(!optrs->isEmpty() && (optrs->top()=='*'|| optrs->top()=='/')){
                int result= compute(optrs->pop(),operands->pop(),operands->pop());
                operands->push(result);
            }
        }else if(qch==')'){
            // evaluate expression whenever closing bracket met
            char optr= optrs->pop();
            int value=operands->pop();
            if(optr!='('){
                // expression within brackets
                int lOprnd= operands->pop();
                if(optrs->pop()!='('){
                    ui->lineEdit->setText("Invalid expression");
    //                throw "Invalid expression";
                }
                value= compute(optr,lOprnd, value);
            }
            operands->push(value);
        }
        else{
            // push in '+-*/('
            // execute all when following operator is add or minus
            if(!optrs->isEmpty() && optrs->top()!='(' && (qch=='+' || qch=='-')){
                int result= compute(optrs->pop(),operands->pop(),
                                    operands->pop());
                operands->push(result);
            }
            optrs->push(qch.toLatin1());
        }
        i++;
    }
}

int Widget::compute(char optr, int l,int r){
    switch (optr){
        case '+':
           return l+r;
        case '-':
           return l-r;
        case '*':
           return l*r;
        case '/':
           return l/r;
        default:
            break;
    }
    return 0;
}
