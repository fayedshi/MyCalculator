#include "widget.h"
#include "ui_widget.h"
#include <QtDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
//        QStack<int> operands;
//        QStack<char> optrs;
    anyNode = MyNode(20);
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
    operands.clear();
    QString expr= ui->lineEdit->text();
    // todo: verify expression first
    if(!verifyExpression(expr)){
        ui->lineEdit->setStyleSheet("background-color:rgba(255,0,0,255)");
        return;
    }
    parseAndCompute(expr);
    if(!optrs.isEmpty()){
        computeAndPack();
    }
    int val= operands.top()->getValue();
    ui->lineEdit->setText(QString::number(val));
    ui->lineEdit->setStyleSheet("");

    qDebug()<<"diapaly="<<anyNode.getLeft()->getValue();
}

// check consucutive operators and redudant brackets
bool Widget::verifyExpression(QString expr){
    int len=expr.length();
    QStack<QChar> stk;
    QChar pre;
    while(len-->0){
        QChar qch =expr.at(len);
        if(qch==')'){
            stk.push(qch);
        }else if(qch=='('){
            if(stk.isEmpty()){
                return false;
            }
            stk.pop();
        }
        else if(qch==pre && (qch <'0' || qch >'9')){
            return false;
        }
        pre=qch;
    }
    if(!stk.isEmpty()){
        return false;
    }
    return true;
}

//int Widget::computeRest(QStack<int> *operands, QStack<char> *optrs){
//    while(!optrs->isEmpty()){
//        operands->push(compute(optrs->pop(),operands->pop(), operands->pop()));
//    }
//    return operands->pop();
//}

void Widget::parseAndCompute(QString expr){
    int i=0, len=expr.length();
    while(i<len){
        QChar qch =expr.at(i);
        if(qch >='0' && qch <='9'){
            QString num;
            while(i< len && expr.at(i) >='0' && expr.at(i) <='9'){
                num.append(expr.at(i++));
            }
            i--;
            MyNode *node= new MyNode(num.toUInt());
            operands.push(node);
            // execute for multiply or divide whenever met
            if(!optrs.isEmpty() && (optrs.top()=='*'|| optrs.top()=='/')){
                computeAndPack();
            }
        }else if(qch==')'){
            // evaluate expression whenever closing bracket met
            //            char optr= optrs->pop();
            if(optrs.top()!='('){
                // expression within brackets
                //                int lOprnd= operands->pop();
                //                if(optrs->pop()!='('){
                //                    ui->lineEdit->setText("Invalid expression");
                //                    //                throw "Invalid expression";
                //                }
                //                value= computeAndPack(optr,lOprnd, value);
                computeAndPack();
                // pop left half bracket
                optrs.pop();
            }else{
                // pop left half bracket
                optrs.pop();
            }

            // check previous operation
            if(!optrs.isEmpty() && (optrs.top()=='*'||optrs.top()=='/') && operands.size()>1){
                computeAndPack();
                //                operands->push(result);
            }
        }else{
            // push in operators
            // execute all when following operator is add, minus
            if(!optrs.isEmpty() && optrs.top()!='(' && (qch=='+' || qch=='-')){
                computeAndPack();
                //                operands->push(result);
            }
            optrs.push(qch.toLatin1());
        }
        i++;
    }
    // todo logic

}

void Widget::computeAndPack(){

    MyNode* right=operands.pop();
    MyNode* left= operands.pop();
    int r=right->getValue();
    int l=left->getValue();
//    MyNode *right=new MyNode(r);
//    MyNode *left= new MyNode(l);
    char optr=optrs.pop();
    int value=0;
    switch (optr){
    case '+':
        value= l+r;
        break;
    case '-':
        value= l-r;
        break;
    case '*':
        value= l*r;
        break;
    case '/':
        value= l/r;
        break;
    default:
        break;
    }
    MyNode *node=new MyNode(left,right,optr,value);
    operands.push(node);
    MyNode *lf=new MyNode(6);
    MyNode *rgt=new MyNode(7);
//    MyNode lf= MyNode(6);
//    MyNode rgt=MyNode(7);// available only within the slot, new keyword creates object on heap
    anyNode.setValue(42);
    anyNode.setLeft(lf);
    anyNode.setRight(rgt);
}

//void checkPrecedence(QStack<int> *operands, QStack<char> *optrs){
//    if(top optr is * or /){
//        if(optrs.size()==1){
//            if(operands size==2){
//                //compute
//            }
//        }else if(operands size==3){
//            //compute
//        }
//    }else if(+ or -){
//        if(operands.size==2){
//            //compute
//        }
//    }else if(')'){
//        if(operands.size==2){
//            //compute
//        }
//        if(top optr * or /){
//            compute
//        }
//    }
//}
//}


void Widget::on_backBtn_clicked()
{
    QString expr=ui->lineEdit->text();
    expr.chop(1);
    ui->lineEdit->setText(expr);
}


void Widget::on_btnClear_clicked()
{
    ui->lineEdit->setText("");
    ui->lineEdit->setStyleSheet("");
}

void Widget::on_btnUndo_clicked()
{
    if(!operands.isEmpty()){
        MyNode* topNode= operands.pop();
        if(topNode->getOptr()!='\r'){
            operands.push(topNode->getLeft());
            operands.push(topNode->getRight());
        }
    }
//    StringBuffer sb = new StringBuffer();
//    for (Result res : stack) {
//        Double value = res.getValue();
//        sb.append(String.format("%.10f", value).replaceFirst("\\.?0+$", "") + " ");
//    }

    QString ops;
    for(MyNode* node: operands){
        ops.append(QString::number(node->getValue())).append(" ");
    }
    ui->lineEdit->setText(ops);
}

