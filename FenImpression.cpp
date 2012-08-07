#include "FenImpression.h"
#include "ui_Dialogimpression.h"

DialogImpression::DialogImpression(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogImpression)
{
    ui->setupUi(this);
}

DialogImpression::~DialogImpression()
{
    delete ui;
}
