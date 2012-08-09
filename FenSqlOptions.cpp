#include "FenSqlOptions.h"
#include "ui_FenSqlOptions.h"

FenSqlOptions::FenSqlOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FenSqlOptions)
{
    ui->setupUi(this);
}

FenSqlOptions::~FenSqlOptions()
{
    delete ui;
}
