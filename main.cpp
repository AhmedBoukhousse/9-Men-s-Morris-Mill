#include "selection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    selection s;
    s.show();
    return a.exec();
}
