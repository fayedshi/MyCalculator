#ifndef MYNODE_H
#define MYNODE_H

class MyNode{
    MyNode *left;
    MyNode *right;
    char optr;
    int value;

public:
    MyNode(){};
    ~MyNode(){};
    MyNode(int val):value(val){}
    MyNode(MyNode *l,MyNode *r, char op, int val):
        left(l),
        right(r),
        optr(op),
        value(val){};
    void setLeft(MyNode *left){
        this->left=left;
    }
    void setRight(MyNode *right){
        this->right=right;
    }
    MyNode* getLeft() {
        return left;
    }
    MyNode* getRight() {
        return right;
    }

    char getOptr() {
        return optr;
    }

    void setOptr(char optr) {
        this->optr = optr;
    }

    int getValue() {
        return value;
    }

    int setValue(int val) {
        this->value= val;
    }

};

#endif // MYNODE_H
