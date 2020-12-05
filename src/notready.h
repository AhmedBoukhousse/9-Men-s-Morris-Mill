#ifndef NOTREADY_H
#define NOTREADY_H

#include <QDialog>

namespace Ui {
class notready;
}

class notready : public QDialog
{
    Q_OBJECT

public:
    explicit notready(QWidget *parent = nullptr);
    ~notready();

private:
    Ui::notready *ui;
};

#endif // NOTREADY_H
