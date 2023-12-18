#ifndef MYNODE_H
#define MYNODE_H

class MyNode{
    MyNode *left=nullptr;
    MyNode *right=nullptr;
    char optr='\0';
    char parentOptr='\0';
    int value;
    bool withBrachets=false;
    int leftBrachet=0;
    int rightBrachet=0;

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

    char getParantOptr() {
        return parentOptr;
    }

    void setParentOptr(char parentOptr) {
        this->parentOptr = parentOptr;
    }

    int getValue() {
        return value;
    }

    void setValue(int val) {
        this->value= val;
    }

    int getLeftBrachet(){
        return leftBrachet;
    }

    void setLeftBrachet(int cnt){
        this->leftBrachet=cnt;
    }

    int getRightBrachet(){
        return rightBrachet;
    }

    void setRightBrachet(int cnt){
        this->rightBrachet=cnt;
    }

    bool getWithBrachets(){
        return withBrachets;
    }

    void setWithBrachet(bool b){
        this->withBrachets=b;
    }

};

#endif // MYNODE_H
