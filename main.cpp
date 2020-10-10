#include "MainWindow.h"
#include "selection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Selection s;
    s.show();
    return a.exec();
}
