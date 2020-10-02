#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSignalMapper>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QPushButton* button;
    ~MainWindow();

private slots:
   void handleButton2(int button);

private:
    Ui::MainWindow *ui;
    bool toggle = true;
    QPushButton* PB[24];
    QSignalMapper *signalMapper;
    int red = 9;
    int black = 9;
    QIcon redIcon;
    QIcon blackIcon;
};
#endif // MAINWINDOW_H
