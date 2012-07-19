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



#include "FenJournalVente.h"
#include "ui_JournalVente.h"

FenJournalVente::FenJournalVente(void)
{
	ui = new Ui::JournalVente();
	ui->setupUi(this);
	ui->dateEdit->setDate(QDate::currentDate());
	ui->tableView_2->setModel(&listevente);
	listevente.setTable("Ticket");
	listevente.setSort(5,Qt::AscendingOrder);
	listevente.setRelation(4,QSqlRelation("Client","id","Nom"));
	listevente.setHeaderData(1,Qt::Horizontal,"Prix caisse");
	listevente.setHeaderData(2,Qt::Horizontal,"Prix bancontact");
	listevente.setHeaderData(3,Qt::Horizontal,"Prix chèques");
	listevente.setHeaderData(4,Qt::Horizontal,"Client");
	listevente.setHeaderData(6,Qt::Horizontal,"N° Ticket");
	QDate curdate = QDate::currentDate();
	listevente.setFilter(QString("DATE(date)='%1/%2/%3'").arg(curdate.year()).arg(curdate.month()).arg(curdate.day()));
	listevente.select();
	ui->tableView_2->setColumnHidden(0,true);
	ui->tableView_2->setColumnHidden(5,true);

	ui->tableView->setModel(&listearticle);
	listearticle.setTable("vente");
	listearticle.select();

	connect(ui->dateEdit,SIGNAL(dateChanged(QDate)),this,SLOT(ChangementDate(QDate)));
	connect(ui->tableView_2->selectionModel(),SIGNAL(currentRowChanged(const QModelIndex &,const QModelIndex &)),this,SLOT(ChangementSel(const QModelIndex &)));
}


FenJournalVente::~FenJournalVente(void)
{
	delete ui;
}
void FenJournalVente::ChangementDate(QDate curdate){
	listevente.setFilter(QString("DATE(date)='%1-%2-%3'").arg(curdate.year()).arg(curdate.month()).arg(curdate.day()));
}
void FenJournalVente::ChangementSel(const QModelIndex &index)
{
	if(index.isValid())
	{
        QSqlRecord record = listearticle.record(index.row());
		int id = record.value("id").toInt();
		listearticle.setFilter(QString("ticket=%1").arg(id));
	}
}
