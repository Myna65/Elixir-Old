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



#include "FenIntroClient.h"
#include "ui_IntroClientWindow.h"
#include <QtSql/QtSql>

FenIntroClient::FenIntroClient(void)
{
	ui=new Ui::IntroClient();
	ui->setupUi(this);
	connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(Accept()));
	connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(reject()));
}
FenIntroClient::~FenIntroClient(void)
{
	delete ui;
}
void FenIntroClient::Accept()
{
	QSqlQuery req;
	req.prepare("INSERT INTO Client (nom,prenom,adresse,codepostal,localite,tel,fax,courriel,remarques) VALUES (:nom,:pre,:adr,:cod,:loc,:tel,:fax,:cou,:rem)");
	req.bindValue(":nom",ui->nomLineEdit->text());
	req.bindValue(":pre",ui->prNomLineEdit->text());
	req.bindValue(":adr",ui->adresseLineEdit->text());
	req.bindValue(":cod",ui->codepostalLineEdit->text());
	req.bindValue(":loc",ui->localitLineEdit->text());
	req.bindValue(":tel",ui->tLPhoneLineEdit->text());
	req.bindValue(":fax",ui->faxLineEdit->text());
	req.bindValue(":cou",ui->eMailLineEdit->text());
	req.bindValue(":rem",ui->remarquesLineEdit->text());
	req.exec();
	accept();
}
