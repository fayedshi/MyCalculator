#include "widget.h"
#include "ui_widget.h"
#include <QtDebug>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
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
    QString expr= ui->lineEdit->text().replace(' ',"");
    if(!verifyExpression(expr)){
        ui->lineEdit->setStyleSheet("background-color:rgba(255,0,0,255)");
        return;
    }
    // clean up arithmetical history before new calculation
    while(!operands.isEmpty()){
        freeChildNodes(operands.pop());
    }
    parseAndCompute(expr);
    if(!optrs.isEmpty()){
        // evaluate last expression
        computeAndPack();
    }
    QString strVal= operands.isEmpty()?    expr:
                                           QString::number(operands.top()->getValue());
    ui->lineEdit->setText(strVal);
    ui->lineEdit->setStyleSheet("");
}

// delete nodes created with 'new' keyword
void Widget::freeChildNodes(MyNode* node){
    if(!node){
        return;
    }
    freeChildNodes(node->getLeft());
    freeChildNodes(node->getRight());
    delete node;
}

// check consucutive operators and redudant brackets
bool Widget::verifyExpression(QString expr){
//    if(!expr.contains(QRegExp("[+\\-*\\/]"))){
//        return false;
//    }
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
        else if(!qch.isNumber()&& !pre.isNumber() && pre!='('){
            return false;
        }
        pre=qch;
    }
    if(!stk.isEmpty()){
        return false;
    }
    return true;
}

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
            if(optrs.top()!='('){
                // expression within brackets
                computeAndPack();
                operands.top()->setWithBrachet(true);
                optrs.pop();
            }else{
                optrs.pop();
            }

            // check previous operation
            if(!optrs.isEmpty() && (optrs.top()=='*'||optrs.top()=='/') && operands.size()>1){
                computeAndPack();
            }
        }else{
            // push in operators
            // execute all when following operator is add, minus
            if(!optrs.isEmpty() && optrs.top()!='(' && (qch=='+' || qch=='-')){
                computeAndPack();
            }
            optrs.push(qch.toLatin1());
        }
        i++;
    }
}

void Widget::computeAndPack(){
    MyNode* right=operands.pop();
    MyNode* left= operands.pop();
    int r=right->getValue();
    int l=left->getValue();
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
    MyNode *parentNode=new MyNode(left,right,optr,value);
    operands.push(parentNode);
    /*
     * FOR Testing
     MyNode *lf=new MyNode(6);
    MyNode *rgt=new MyNode(7);
    anyNode.setValue(42);
    anyNode.setLeft(lf);
    anyNode.setRight(rgt);
*/

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
    MyNode* topNode;
    if(!operands.isEmpty()){
        topNode= operands.pop();
        //        qDebug()<<"top node optr"<<topNode->getOptr();
        if(topNode->getOptr()!='\0'){
            //            qDebug()<<"push child nodes";
            MyNode* left=topNode->getLeft();
            MyNode* right=topNode->getRight();
            left->setParentOptr(topNode->getOptr());
            operands.push(left);
            operands.push(right);
            if(topNode->getWithBrachets()){
                right->setRightBrachet(topNode->getRightBrachet()+1);
                left->setLeftBrachet(topNode->getLeftBrachet()+1);
            }
        }
        delete topNode;
    }
    QString ops;
    //    qDebug()<<"to list value";
    for(MyNode* node: operands){
        ops=ops.append(printNode(node));
    }
    ui->lineEdit->setText(ops);
}

QString Widget::printNode(MyNode* node){
    QString str;
    int i=0;
    while(i++<node->getLeftBrachet()){
        str.append("(");
    }
    str.append(QString::number(node->getValue()));
    if(node->getParantOptr()){
        str.append(node->getParantOptr());
    }
    i=0;
    while(i++<node->getRightBrachet()){
        str.append(")");
    }
    return str;
}
