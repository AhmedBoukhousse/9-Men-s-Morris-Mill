#include "selection.h"
#include "ui_selection.h"
Selection::Selection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Selection)
{
    ui->setupUi(this);
    setWindowTitle(tr("Player Selection"));
}

Selection::~Selection()
{
    delete ui;
}
