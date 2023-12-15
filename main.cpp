#include "widget.h"

#include <QApplication>
class message; // This is available in all editors.
        QStack<int> operands;
        QStack<char> optrs;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
