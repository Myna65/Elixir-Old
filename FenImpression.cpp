#include "FenImpression.h"
#include "ui_Dialogimpression.h"
#include <QtCore/qsettings.h>
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
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(imprimer()));
    connect(ui->checkBox_5,SIGNAL(clicked()),this,SLOT(toupdate()));
    connect(ui->checkBox_6,SIGNAL(clicked()),this,SLOT(toupdate()));
    connect(ui->checkBox_7,SIGNAL(clicked()),this,SLOT(toupdate()));
    connect(ui->checkBox_8,SIGNAL(clicked()),this,SLOT(toupdate()));
    connect(ui->checkBox_9,SIGNAL(clicked()),this,SLOT(toupdate()));
    QSettings settings("Gestion","Elixir");
    settings.beginGroup("Impression/Centralisee");
    ui->dateEdit->setDate(settings.value("Dateg",QDate::currentDate()).toDate());
    ui->dateEdit_2->setDate(settings.value("Dated",QDate::currentDate()).toDate());
    ui->checkBox->setChecked(settings.value("1",false).toBool());
    ui->checkBox_2->setChecked(settings.value("2",false).toBool());
    ui->checkBox_3->setChecked(settings.value("3",false).toBool());
    ui->checkBox_4->setChecked(settings.value("4",false).toBool());
    ui->checkBox_5->setChecked(settings.value("5",false).toBool());
    ui->checkBox_6->setChecked(settings.value("6",false).toBool());
    ui->checkBox_7->setChecked(settings.value("7",false).toBool());
    ui->checkBox_8->setChecked(settings.value("8",false).toBool());
    ui->checkBox_9->setChecked(settings.value("9",false).toBool());
    ui->checkBox_10->setChecked(settings.value("10",false).toBool());
    ui->checkBox_11->setChecked(settings.value("11",false).toBool());
    ui->checkBox_12->setChecked(settings.value("12",false).toBool());
    ui->checkBox_13->setChecked(settings.value("13",false).toBool());
    ui->checkBox_14->setChecked(settings.value("14",false).toBool());
    ui->checkBox_15->setChecked(settings.value("15",false).toBool());
    ui->checkBox_16->setChecked(settings.value("16",false).toBool());
    toupdate();
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
    QSettings settings("Gestion","Elixir");
    settings.beginGroup("Impression/Centralisee");
    settings.setValue("1",ui->checkBox->isChecked());
    settings.setValue("2",ui->checkBox_2->isChecked());
    settings.setValue("3",ui->checkBox_3->isChecked());
    settings.setValue("4",ui->checkBox_4->isChecked());
    settings.setValue("5",ui->checkBox_5->isChecked());
    settings.setValue("6",ui->checkBox_6->isChecked());
    settings.setValue("7",ui->checkBox_7->isChecked());
    settings.setValue("8",ui->checkBox_8->isChecked());
    settings.setValue("9",ui->checkBox_9->isChecked());
    settings.setValue("10",ui->checkBox_10->isChecked());
    settings.setValue("11",ui->checkBox_11->isChecked());
    settings.setValue("12",ui->checkBox_12->isChecked());
    settings.setValue("13",ui->checkBox_13->isChecked());
    settings.setValue("14",ui->checkBox_14->isChecked());
    settings.setValue("15",ui->checkBox_15->isChecked());
    settings.setValue("16",ui->checkBox_16->isChecked());
    settings.setValue("Dateg",ui->dateEdit->date());
    settings.setValue("Dated",ui->dateEdit_2->date());
}
void FenImpression::toupdate()
{
    if(ui->checkBox_9->isChecked())
    {
        ui->groupBox->setEnabled(false);
        ui->groupBox_4->setEnabled(false);
        ui->checkBox_11->setEnabled(false);
        ui->checkBox_12->setEnabled(false);
        ui->checkBox_16->setEnabled(false);
    }
    else
    {
        ui->groupBox->setEnabled(true);
        ui->groupBox_4->setEnabled(true);
        ui->checkBox_11->setEnabled(true);
        ui->checkBox_12->setEnabled(true);
        ui->checkBox_16->setEnabled(true);
    }
    if((ui->checkBox_5->isChecked()==false)&&(ui->checkBox_6->isChecked()==false)&&(ui->checkBox_7->isChecked()==false)&&(ui->checkBox_8->isChecked()==false))
    {
        ui->checkBox_13->setEnabled(false);
    }
    else
    {
        ui->checkBox_13->setEnabled(true);
    }
    if((ui->checkBox_5->isChecked()==false)&&(ui->checkBox_6->isChecked()==false)&&(ui->checkBox_7->isChecked()==false)&&(ui->checkBox_8->isChecked()==false)&&(ui->checkBox_9->isChecked()))
    {
        ui->pushButton->setEnabled(false);
        ui->checkBox_10->setEnabled(false);
    }
    else
    {
        ui->pushButton->setEnabled(true);
        ui->checkBox_10->setEnabled(true);
    }
}
