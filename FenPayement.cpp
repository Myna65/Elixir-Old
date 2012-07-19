////////////////////////////////////////////////////////////////////////////////
//
//    Elixir, programme de gestion de stock et de clients.
//    Copyright (C) 2012 Meynaert Nathan
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////////



#include "FenPayement.h"
#include "ui_PayementWindow.h"


FenPayement::FenPayement(float t_valeur)
{
	ui = new Ui::Payement();
	ui->setupUi(this);
	valeur=t_valeur;
	ui->totalDoubleSpinBox->setValue(valeur);

	connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(Accept()));
	connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(reject()));
	connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(PayBanc()));
	connect(ui->payBancontactDoubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(UpRend()));
	connect(ui->payCashDoubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(UpRend()));
	connect(ui->doubleSpinBox,SIGNAL(valueChanged(double)),this,SLOT(UpRend()));
}
FenPayement::~FenPayement(void)
{
	delete ui;
}
void FenPayement::setValue(float value)
{
	valeur=value;
}
float FenPayement::Cash()
{
	return cash;
}
float FenPayement::Banque()
{
	return banque;
}
float FenPayement::Cheque()
{
	return cheque;
}
void FenPayement::Accept()
{
	cheque=ui->doubleSpinBox->value();
	banque=ui->payBancontactDoubleSpinBox->value();
	cash=ui->payCashDoubleSpinBox->value();
	if(valeur>cheque+banque+cash)
	{
		QMessageBox::critical(this,"Erreur",QString("La somme doit faire %1 et elle fait %2").arg(valeur).arg(cheque+banque+cash));
		return;
	}
	cash+=(valeur-(cheque+banque+cash));
	emit accept();
}
void FenPayement::PayBanc()
{
	cheque=0.;
	cash=0.;
	banque=valeur;
	emit accept();
}
void FenPayement::UpRend()
{
	double reste=ui->totalDoubleSpinBox->value();
	reste-=ui->payCashDoubleSpinBox->value();
	reste-=ui->payBancontactDoubleSpinBox->value();
	reste-=ui->doubleSpinBox->value();
	if(reste<0)
	{
		ui->renduDoubleSpinBox->setValue(-reste);
	}
	else
	{
		ui->renduDoubleSpinBox->setValue(0);
	}
}
