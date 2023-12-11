#ifndef MYNODE_H
#define MYNODE_H

class MyNode{
    MyNode *left;
    MyNode *right;
    char optr;
    int value;

  public:
    MyNode(int val):value(val){}
    MyNode(MyNode *l,MyNode *r, char op, int val):
        left(l),
        right(r),
        optr(op),
        value(val){};
};

#endif // MYNODE_H
