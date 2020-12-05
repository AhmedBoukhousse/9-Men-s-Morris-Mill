#include "notready.h"
#include "ui_notready.h"

notready::notready(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notready)
{
    ui->setupUi(this);
}

notready::~notready()
{
    delete ui;
}
