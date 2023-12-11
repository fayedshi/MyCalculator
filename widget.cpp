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
    operands.clear();
    QString expr= ui->lineEdit->text();
    // todo: verify expression first
    if(!verifyExpression(expr)){
        ui->lineEdit->setStyleSheet("background-color:rgba(255,0,0,255)");
        return;
    }
    parseAndCompute(expr,&operands,&optrs);
    // now operands stack and operators stack is loaded
    computeRest(&operands,&optrs);
    ui->lineEdit->setText(QString::number(*(operands.top().getValue())));
    ui->lineEdit->setStyleSheet("");
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

 void Widget::computeRest(QStack<MyNode> *operands, QStack<char> *optrs){
    while(!optrs->isEmpty()){
//        operands->push(compute(optrs->pop(),operands->pop(), operands->pop()));
        MyNode right= operands->pop();
        MyNode left= operands->pop();
        int result= compute(optrs->top(),left,right);
        MyNode node= MyNode(&left,&right,optrs->pop(),&result);
        operands->push(node);
    }
//    return operands.top();
}

void Widget::parseAndCompute(QString expr, QStack<MyNode> *operands, QStack<char> *optrs){
    int i=0, len=expr.length();
    while(i<len){
        QChar qch =expr.at(i);
        if(qch >='0' && qch <='9'){
            QString num;
            while(i< len && expr.at(i) >='0' && expr.at(i) <='9'){
                num.append(expr.at(i++));
            }
            i--;
            int val=num.toUInt();
            MyNode node=MyNode(&val);
            operands->push(node);
            // execute for multiply or divide whenever met

            if(!optrs->isEmpty() && (optrs->top()=='*'|| optrs->top()=='/')){
                char optr=optrs->pop();
                MyNode right=operands->pop();
                MyNode left= operands->pop();
                int result= compute(optr,left,right);
//                node=MyNode(left,right,optr,result);
                operands->push(MyNode(&left,&right,optr,&result));
            }
        }else if(qch==')'){
            // todo: a bug here 8/(2*2)*2
            // evaluate expression whenever closing bracket met
            char optr= optrs->pop();
            MyNode value=operands->pop();
            MyNode res=value;
            if(optr!='('){
                // expression within brackets
                MyNode lOprnd= operands->pop();
                if(optrs->pop()!='('){
                    ui->lineEdit->setText("Invalid expression");
    //                throw "Invalid expression";
                }
                int num= compute(optr,lOprnd, value);
                res=MyNode(&num);
                res.setOptr(optr);
            }
            operands->push(res);
        }else{
            // push in operators
            // execute all when following operator is add or minus
            if(!optrs->isEmpty() && optrs->top()!='(' && (qch=='+' || qch=='-')){
                MyNode right=operands->pop();
                MyNode left= operands->pop();
                char optr=optrs->pop();
                int result= compute(optr,left,right);
//                int result= compute(optrs->pop(),operands->pop(),
//                                    operands->pop());
                MyNode *node=new MyNode(&left,&right,optr,&result);
                operands->push(*node);
//                operands->push(result);
            }
            optrs->push(qch.toLatin1());
        }
        i++;
    }
}

int Widget::compute(char optr, MyNode l,MyNode r){
    switch (optr){
        case '+':
           return *(l.getValue())+*(r.getValue());
        case '-':
            return *(l.getValue())-*(r.getValue());
        case '*':
           return *(l.getValue())*(*(r.getValue()));
        case '/':
           return *(l.getValue())/(*(r.getValue()));
        default:
            break;
    }
    return 0;
}

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
        MyNode topNode= operands.pop();
        if(topNode.getOptr()){
            operands.push(*topNode.getLeftOprnd());
            operands.push(*topNode.getRightOprnd());
        }
    }
//    StringBuffer sb = new StringBuffer();
//    for (Result res : stack) {
//        Double value = res.getValue();
//        sb.append(String.format("%.10f", value).replaceFirst("\\.?0+$", "") + " ");
//    }

    QString ops;
    for(MyNode node: operands){
        ops.append(QString::number(*node.getValue())).append(" ");
    }
    ui->lineEdit->setText(ops);
}

