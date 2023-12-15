#ifndef GLOBAL_H

#define GLOBAL_H

#include <QString>

#include <QtDebug>



class message     //新建一个类存放全局变量

{

public:

     static QString display;
     static QStack<int> operands;
     static QStack<char> optrs;

};

#endif // GLOBAL_H
