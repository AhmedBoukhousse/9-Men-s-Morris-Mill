#ifndef SELECTION_H
#define SELECTION_H

#include <QWidget>

namespace Ui {
class Selection;
}

class Selection : public QWidget
{
    Q_OBJECT

public:
    explicit Selection(QWidget *parent = nullptr);
    ~Selection();
public slots:
 void openGameBoard();
private slots:
void on_onePlayer_clicked();
private:
    Ui::Selection *ui;
    MainWindow *gameBoard;
};

#endif // SELECTION_H
