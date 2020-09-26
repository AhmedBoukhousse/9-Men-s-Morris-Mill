#include "MainWindow.h"
#include "selection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Selection s;
    w.show();
    s.show();
    return a.exec();
}
