#include "FenImpression.h"
#include "ui_Dialogimpression.h"
struct Totaux
{
    bool quot;
    bool hebd;
    bool mens;
    bool annu;
    bool caisse;
    bool actif;
};
struct Caisse
{
    bool actif;
    bool externes;
};
struct Texte
{
    bool actif;
    Caisse caisse;
    bool periodesfin;
    bool clients;
    bool details;
    Totaux totaux;
};
struct Recap
{
    bool actif;
    Totaux totaux;
};
struct Options
{
    Recap recap;
    Texte texte;
};

FenImpression::FenImpression(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogImpression)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    ui->dateEdit_2->setDate(QDate::currentDate());
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(imprimer()));
}

FenImpression::~FenImpression()
{
    delete ui;
}
void FenImpression::imprimer()
{
    Options opt;
    if(ui->checkBox_9->isChecked())
    {
        opt.texte.actif=false;
    }
    else
    {
        opt.texte.actif=true;
        opt.texte.periodesfin=ui->checkBox_10->isChecked();
        opt.texte.totaux.quot=ui->checkBox->isChecked();
        opt.texte.totaux.hebd=ui->checkBox_2->isChecked();
        opt.texte.totaux.mens=ui->checkBox_3->isChecked();
        opt.texte.totaux.annu=ui->checkBox_4->isChecked();
        opt.texte.clients=ui->checkBox_14->isChecked();
        opt.texte.details=ui->checkBox_15->isChecked();
        if((opt.texte.totaux.quot==opt.texte.totaux.hebd)&&(opt.texte.totaux.hebd==opt.texte.totaux.mens)&&(opt.texte.totaux.mens==opt.texte.totaux.annu)&&(opt.texte.totaux.annu==false))
        {
            opt.texte.totaux.actif=false;
        }
        else
        {
            opt.texte.totaux.actif=true;
            opt.texte.totaux.caisse=ui->checkBox_12->isChecked();
        }
        if(ui->checkBox_11->isChecked())
        {
            opt.texte.caisse.actif=true;
            opt.texte.caisse.externes=ui->checkBox_16->isChecked();
        }
        else
        {
            opt.texte.caisse.actif=false;
        }
    }
    opt.recap.totaux.quot=ui->checkBox_5->isChecked();
    opt.recap.totaux.hebd=ui->checkBox_6->isChecked();
    opt.recap.totaux.mens=ui->checkBox_7->isChecked();
    opt.recap.totaux.annu=ui->checkBox_8->isChecked();
    if((opt.recap.totaux.quot==opt.recap.totaux.hebd)&&(opt.recap.totaux.hebd==opt.recap.totaux.mens)&&(opt.recap.totaux.mens==opt.recap.totaux.annu)&&(opt.recap.totaux.annu==false))
    {
        opt.recap.actif=false;
        opt.recap.totaux.actif=false;

    }
    else
    {
        opt.recap.actif=true;
        opt.recap.totaux.actif=true;
        opt.recap.totaux.caisse=ui->checkBox_13->isChecked();
    }
}
