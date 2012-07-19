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



#include "FenSQL.h"
#include "ui_WinSQL.h"
#include <QtSql/QtSql>
#include <QtGui/QtGui>

FenSQL::FenSQL(QWidget *parent) : QWidget(parent) , ui(new Ui::Form)
{
	enum {
        ARTICLE_ID = 0,
        ARTICLE_TITRE = 1,
        ARTICLE_AUTEUR = 2,
        ARTICLE_RUBRIQUE = 3
    };

    enum {
        CHAPITRE_ID = 0,
        CHAPITRE_TITRE = 1,
        CHAPITRE_ARTICLE = 2
    };

    ui->setupUi(this);
	QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("MysqlDSN");
	
	modelArticle = new QSqlRelationalTableModel(this);
	modelArticle->setTable("Article");
	modelArticle->setRelation(ARTICLE_RUBRIQUE,QSqlRelation("Rubrique","id_rubrique","libelle_rubrique"));
	modelArticle->setSort(ARTICLE_TITRE,Qt::AscendingOrder);
	modelArticle->setHeaderData(ARTICLE_RUBRIQUE, Qt::Horizontal, "Rubrique");
    modelArticle->setHeaderData(ARTICLE_TITRE, Qt::Horizontal, "Titre");
    modelArticle->setHeaderData(ARTICLE_AUTEUR, Qt::Horizontal, "Auteur");
	modelArticle->select();

	modelChapitre = new QSqlRelationalTableModel(this);
	modelChapitre->setTable("Chapitre");
	modelChapitre->setSort(ARTICLE_TITRE,Qt::AscendingOrder);
	modelChapitre->setHeaderData(CHAPITRE_TITRE,Qt::Horizontal,"Titre du Chapitre");
	modelChapitre->select();

	ui->tableView->setModel(modelArticle);
	ui->tableView->setItemDelegate(new QSqlRelationalDelegate(this));
	ui->tableView->setColumnHidden(ARTICLE_ID,true);
	ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableView->resizeColumnsToContents();

	ui->tableView_2->setModel(modelChapitre);
	ui->tableView_2->setItemDelegate(new QSqlRelationalDelegate(this));
	ui->tableView_2->setColumnHidden(CHAPITRE_ID,true);
	ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableView_2->resizeColumnsToContents();connect(ui->tableView->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &,const QModelIndex &)),this, SLOT(changementArticle(const QModelIndex &)));
}
FenSQL::~FenSQL()
{
    delete ui;
}
void FenSQL::changementArticle(const QModelIndex &index)
{
	if(index.isValid())
	{
		QSqlRecord record = modelArticle->record(index.row());
		int id=record.value("id_article").toInt();
		modelChapitre->setFilter(QString("id_article = %1").arg(id));
	}
}
