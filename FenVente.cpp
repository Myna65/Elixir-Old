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



#include "FenVente.h"
#include "ui_VenteWindow.h"
#include <set>
#include <QtSql/QtSql>
double arrondir(double val,int dec)
{
	int ival=val*pow(10.,dec+1);
	if(ival%10!=0)
	{
		ival+=10;
	}
	ival/=10;
	return ((double)ival)/pow(10.,dec);
}
FenVente::FenVente()
{
	ui = new Ui::VenteWindow();
	ui->setupUi(this);
	ui->dateEdit->setDate(QDate::currentDate());

	QStringList header;
	header<<"Code"<<"Modle"<<"N Article"<<"Coloris"<<"Taille"<<"Quantit"<<"Prix";

	listecompte=0;
	liste=new QStandardItemModel(0,6,this);
	liste->setHorizontalHeaderLabels(header);

	model = new QSqlTableModel();
	model->setTable("Acompte");
	ui->tableView_2->setModel(model);
	ui->tableView_2->setColumnHidden(0,true);
	ui->tableView_2->setColumnHidden(1,true);
	ui->tableView_2->setColumnHidden(4,true);
	ui->tableView_2->setColumnHidden(5,true);
	ui->tableView_2->setColumnHidden(6,true);
	model->setHeaderData(2,Qt::Horizontal,"Montant");
	model->setHeaderData(3,Qt::Horizontal,"Date introduction");

	ui->tableView->setModel(liste);

	QSqlQuery req;
	req.exec("SELECT id,Nom,Prenom, Adresse, codepostal,localite FROM Client ORDER BY Nom,Prenom,Adresse");
	ui->clientComboBox->addItem("DIVERS");
	clients.push_back(1);
	while(req.next())
	{
		if(req.value(0).toInt()!=1)
		{
			ui->clientComboBox->addItem(QString("%1 %2 %3 %4 %5").arg(req.value(1).toString()).arg(req.value(2).toString()).arg(req.value(3).toString()).arg(req.value(4).toString()).arg(req.value(5).toString()));
			clients.push_back(req.value(0).toInt());
		}
	}
	req.exec("CALL TicNum(CURDATE())");
	req.next();
	ui->spinBox_3->setValue(req.value(0).toInt());
	curclient=0;

	connect(ui->clientComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(ClientChange(int)));
	connect(ui->bCode,SIGNAL(clicked()),this,SLOT(BoutonCode()));
	connect(ui->bEffacer,SIGNAL(clicked()),this,SLOT(BoutonTEffacer()));
	connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(BoutonSEffacer()));
	connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(DeduireAcompte()));
	connect(ui->bAcompte,SIGNAL(clicked()),this,SLOT(AjouterAcompte()));
	connect(ui->bManuel,SIGNAL(clicked()),this,SLOT(BoutonManuel()));
	connect(ui->bValider,SIGNAL(clicked()),this,SLOT(BoutonValider()));
}
void FenVente::BoutonValider()
{
	float somme=0.0;
	for(int i=0;i<liste->rowCount();i++)
	{
		somme+=liste->item(i,6)->text().toFloat();
	}
	FenPayement pay(somme); 
	pay.setValue(somme);
	if(pay.exec()==QDialog::Rejected)
	{
		return;
	}
	QSqlQuery req;
	req.prepare("INSERT INTO Ticket (client,PrixB,PrixC,PrixD,num,date) VALUES (:cli,:b,:c,:d,:num,NOW())");
	req.bindValue(":cli",clients[curclient]);
	req.bindValue(":b",pay.Banque());
	req.bindValue(":c",pay.Cash());
	req.bindValue(":d",pay.Cheque());
	req.bindValue(":num",ui->spinBox_3->value());
	req.exec();
	req.prepare("CALL Alter_solde(:solde)");
	req.bindValue(":solde",pay.Cash());
	req.exec();
	req.prepare("SELECT id FROM Ticket WHERE num=:num AND DATE(date)=CURDATE() AND client=:cli");
	req.bindValue(":cli",clients[curclient]);
	req.bindValue(":num",ui->spinBox_3->value());
	req.exec();
	req.next();
	int idticket=req.value(0).toInt();
	for(int i=0,c=liste->rowCount();i<c;i++)
	{
		QString entete=liste->item(i)->text();
		if(entete=="A-")
		{
			req.prepare("SELECT id FROM Acompte WHERE client = :cli AND Valeur= :mon AND datededuit='0000-00-00'");
			req.bindValue(":mon",-(liste->item(i,6)->text().toInt()));
			req.bindValue(":cli",clients[curclient]);
			req.exec();
			if(req.next())
			{
				int idacompte=req.value(0).toInt();
				req.prepare("UPDATE Acompte SET datededuit=CURDATE(),tickdeduit=:tic WHERE id=:id");
				req.bindValue(":id",idacompte);
				req.bindValue(":tic",idticket);
				req.exec();
			}
			else
			{
				QMessageBox::critical(this,"Erreur","Une dduction d'acompte n'a pu tre correctement effectue : l'acompte n'a pu tre retrouv");
			}
		}
		else if(entete=="A+")
		{
			req.prepare("INSERT INTO Acompte(client,valeur,dateintro,tickintro) VALUES (:cli,:mon,CURDATE(),:tic)");
			req.bindValue(":cli",clients[curclient]);
			req.bindValue(":mon",liste->item(i,6)->text().toInt());
			req.bindValue(":tic",idticket);
			req.exec();
		}
		else if(entete=="?")
		{
			req.prepare("INSERT INTO ventenonreconnue(Modele,NArticle,Coloris,Taille,Qt,Prix,Ticket) VALUES (:mod,:art,:col,:tai,:qt,:prix,:tic)");
			req.bindValue(":mod",liste->item(i,1)->text());
			req.bindValue(":art",liste->item(i,2)->text());
			req.bindValue(":col",liste->item(i,3)->text());
			req.bindValue(":tai",liste->item(i,4)->text());
			req.bindValue(":qt",liste->item(i,5)->text().toInt());
			req.bindValue(":prix",(liste->item(i,6)->text().toFloat())/(liste->item(i,5)->text().toInt()));
			req.bindValue(":tic",idticket);
			req.exec();
		}
		else
		{
			req.prepare("CALL vendre(:tic,:code,:qt,:prix)");
			req.bindValue(":tic",idticket);
			req.bindValue(":code",liste->item(i,0)->text().toInt());
			req.bindValue(":qt",liste->item(i,5)->text().toInt());
			req.bindValue(":prix",liste->item(i,6)->text().toFloat());
			req.exec();
		}
	}
	system(QString("%userprofile%/Gestion/ElixiP.exe 0 %1").arg(idticket).toStdString().c_str());
	req.exec("SELECT id,Nom,Prenom, Adresse, codepostal,localite FROM Client ORDER BY Nom,Prenom,Adresse");
	ui->clientComboBox->clear();
	ui->clientComboBox->addItem("DIVERS");
	clients.clear();
	clients.push_back(1);
	while(req.next())
	{
		if(req.value(0).toInt()!=1)
		{
			ui->clientComboBox->addItem(QString("%1 %2 %3 %4 %5").arg(req.value(1).toString()).arg(req.value(2).toString()).arg(req.value(3).toString()).arg(req.value(4).toString()).arg(req.value(5).toString()));
			clients.push_back(req.value(0).toInt());
		}
	}
	req.exec("CALL TicNum(CURDATE())");
	req.next();
	ui->spinBox_3->setValue(req.value(0).toInt());
	liste->removeRows(0,liste->rowCount());
	listecompte=0;
}
void FenVente::BoutonCode()
{
	QSqlQuery req;
	req.prepare("SELECT id,modele,Narticle,coloris,taille,PV FROM inventaire WHERE id=:id");
	req.bindValue(":id",ui->codeSpinBox->value());
	req.exec();
	if(req.next())
	{
		double prix=ui->prixRondDoubleSpinBox->value();
		if(prix==0)
		{
			prix=req.value(5).toDouble();
		}
		prix*=1.0-(ui->spinBox->value()/100.0);
		prix*=ui->spinBox_2->value();
		liste->appendRow(0);
		liste->setItem(listecompte,0,new QStandardItem(req.value(0).toString()));
		liste->setItem(listecompte,1,new QStandardItem(req.value(1).toString()));
		liste->setItem(listecompte,2,new QStandardItem(req.value(2).toString()));
		liste->setItem(listecompte,3,new QStandardItem(req.value(3).toString()));
		liste->setItem(listecompte,4,new QStandardItem(req.value(4).toString()));
		liste->setItem(listecompte,5,new QStandardItem(QString("%1").arg(ui->spinBox_2->value())));
		liste->setItem(listecompte,6,new QStandardItem(QString("%1").arg(arrondir(prix,1))));
		listecompte++;

		ui->spinBox_2->setValue(1);
		ui->codeSpinBox->setValue(0);
		ui->prixRondDoubleSpinBox->setValue(0);
	}
	else
	{
		QMessageBox::critical(this,"Aucun code","Aucun lment avec ce code trouv");
	}
}
FenVente::~FenVente()
{
	delete ui;
}
void FenVente::BoutonTEffacer()
{
	liste->removeRows(0,liste->rowCount());
	listecompte=0;
}
void FenVente::BoutonSEffacer()
{
	QModelIndexList modellist=ui->tableView->selectionModel()->selectedRows();
	std::set<int,invless<int> > list;
	for(int i=0,c=modellist.size();i<c;i++)
	{
		int numligne =modellist[i].row();
		list.insert(numligne);
	}
	listecompte-=list.size();
	for(std::set<int,invless<int> >::iterator it = list.begin();it!=list.end();it++)
	{
		liste->removeRow(*it);
	}
}
void FenVente::ClientChange(int current)
{
	if(current!=-1)
	{
		curclient=current;
		model->setFilter(QString("datededuit = '0000-00-00' AND client=%1").arg(clients[current]));
		model->select();
	}
}
void FenVente::DeduireAcompte()
{
	QModelIndex index=ui->tableView_2->selectionModel()->currentIndex();
	double prix=model->data(index).toInt();
	if(prix!=0)
	{
		liste->appendRow(0);
		liste->setItem(listecompte,0,new QStandardItem("A-"));
		liste->setItem(listecompte,1,new QStandardItem(""));
		liste->setItem(listecompte,2,new QStandardItem(""));
		liste->setItem(listecompte,3,new QStandardItem(""));
		liste->setItem(listecompte,4,new QStandardItem(""));
		liste->setItem(listecompte,5,new QStandardItem("1"));
		liste->setItem(listecompte,6,new QStandardItem(QString("%1").arg(-prix)));
		listecompte++;
	}
}
void FenVente::AjouterAcompte()
{
	double prix=ui->valeurDoubleSpinBox->value();
	if(prix!=0)
	{
		liste->appendRow(0);
		liste->setItem(listecompte,0,new QStandardItem("A+"));
		liste->setItem(listecompte,1,new QStandardItem(""));
		liste->setItem(listecompte,2,new QStandardItem(""));
		liste->setItem(listecompte,3,new QStandardItem(""));
		liste->setItem(listecompte,4,new QStandardItem(""));
		liste->setItem(listecompte,5,new QStandardItem("1"));
		liste->setItem(listecompte,6,new QStandardItem(QString("%1").arg(prix)));
		listecompte++;
	}
}
void FenVente::BoutonManuel()
{
	QSqlQuery req;
	req.prepare("SELECT * FROM inventaire WHERE modele=:mod AND NArticle=:art AND Taille=:tai AND Coloris=:col");
	req.bindValue(":mod",ui->aricleLineEdit->text());
	req.bindValue(":art",ui->nArticleLineEdit->text());
	req.bindValue(":tai",ui->colorisLineEdit->text());
	req.bindValue(":col",ui->tailleLineEdit->text());
	req.exec();
	if(!req.next())
	{
		if(QMessageBox::question(this,"Confirmation","Pas de correspondance avec le stock trouve. Continuer ?",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
		{
			double prix=ui->prixDoubleSpinBox->value();
			prix*=1.0-(ui->soldesSpinBox->value()/100.0);
			prix*=ui->quantitSpinBox->value();
			liste->appendRow(0);
			liste->setItem(listecompte,0,new QStandardItem("?"));
			liste->setItem(listecompte,1,new QStandardItem(ui->aricleLineEdit->text()));
			liste->setItem(listecompte,2,new QStandardItem(ui->nArticleLineEdit->text()));
			liste->setItem(listecompte,3,new QStandardItem(ui->tailleLineEdit->text()));
			liste->setItem(listecompte,4,new QStandardItem(ui->colorisLineEdit->text()));
			liste->setItem(listecompte,5,new QStandardItem(QString("%1").arg(ui->quantitSpinBox->value())));
			liste->setItem(listecompte,6,new QStandardItem(QString("%1").arg(arrondir(prix,1))));
			listecompte++;
		}
	}
	else
	{
		double prix=ui->prixDoubleSpinBox->value();
		prix*=1.0-(ui->soldesSpinBox->value()/100.0);
		prix*=ui->quantitSpinBox->value();
		liste->appendRow(0);
		liste->setItem(listecompte,0,new QStandardItem(req.value(0).toString()));
		liste->setItem(listecompte,1,new QStandardItem(ui->aricleLineEdit->text()));
		liste->setItem(listecompte,2,new QStandardItem(ui->nArticleLineEdit->text()));
		liste->setItem(listecompte,3,new QStandardItem(ui->tailleLineEdit->text()));
		liste->setItem(listecompte,4,new QStandardItem(ui->colorisLineEdit->text()));
		liste->setItem(listecompte,5,new QStandardItem(QString("%1").arg(ui->quantitSpinBox->value())));
		liste->setItem(listecompte,6,new QStandardItem(QString("%1").arg(arrondir(prix,1))));
		listecompte++;
	}
}
