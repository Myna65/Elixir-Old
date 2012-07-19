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



#include "FenPrincipale.h"
#include "ui_MainWindow.h"
#include "FenVente.h"
#include "FenIntroClient.h"
#include "FenJournalVente.h"
#include "FenIntrodate.h"
#include "FenCaisse.h"
#include "FenACaisse.h"
#include "FenClient.h"
#include "FenIntroFacture.h"
#include <QtGui/QtGui>
#include <QtSql/QtSql>

FenPrincipale::FenPrincipale(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow),currentWidget(0)
{
	ui->setupUi(this);

	connect(ui->actionQuitter,SIGNAL(triggered()),qApp,SLOT(quit()));
	connect(ui->actionImprimer_par_ordre_alphab_tque,SIGNAL(triggered()),this,SLOT(ImprimerFournisseur()));
	connect(ui->action_cran_de_vente,SIGNAL(triggered()),this,SLOT(OuvrirVente()));
	connect(ui->actionNouveau_client,SIGNAL(triggered()),this,SLOT(OuvrirIntroClient()));
	connect(ui->actionJournal_des_ventes,SIGNAL(triggered()),this,SLOT(OuvrirJournalVente()));
	connect(ui->actionImprimer_le_journal_des_ventes,SIGNAL(triggered()),this,SLOT(ImprimerJournalVente()));
	connect(ui->actionTotal_vente,SIGNAL(triggered()),this,SLOT(ImprimerTotalJournalVente()));
	connect(ui->actionListe_des_mouvements_caisse,SIGNAL(triggered()),this,SLOT(OuvrirCaisse()));
	connect(ui->actionAjouter_un_mouvement_caisse,SIGNAL(triggered()),this,SLOT(OuvrirIntroCaisse()));
	connect(ui->actionImprimer_livre_caisse,SIGNAL(triggered()),this,SLOT(ImprimerJournalCaisse()));
	connect(ui->actionListe_des_clients,SIGNAL(triggered()),this,SLOT(OuvrirClient()));
	connect(ui->actionImprimer_la_liste,SIGNAL(triggered()),this,SLOT(ImprimerClient()));
	connect(ui->actionAjouter_une_facture,SIGNAL(triggered()),this,SLOT(OuvrirIntroFacture()));
}
void FenPrincipale::ImprimerFournisseur()
{
	QPrinter * printer = new QPrinter(QPrinter::HighResolution);
	printer->setPaperSize (QPrinter::A4);
	printer->setOutputFormat (QPrinter::NativeFormat);
	printer->setOrientation(QPrinter::Landscape);  
	printer->setFullPage(true);
	QPrintDialog printDialog(printer,this);
	if(printDialog.exec()==QDialog::Accepted)
	{
		QTextCharFormat NormalFormat;
		QTextCharFormat ItalicFormat;
		ItalicFormat.setFontItalic(true);
		QTextCharFormat TitleFormat;
		TitleFormat.setFontPointSize(15);
		TitleFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
		TitleFormat.setFontWeight(QFont::Bold);
		TitleFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
		QTextBrowser* editor = new QTextBrowser;
		QDate date = QDate::currentDate();
		QTime heure = QTime::currentTime();
		editor->setAlignment(Qt::AlignLeft);
		editor->setCurrentCharFormat(ItalicFormat);
		editor->append(date.toString("dddd dd MMMM yyyy")+" "+heure.toString("hh:mm:ss")+"/n");
		editor->setAlignment(Qt::AlignCenter);
		editor->setCurrentCharFormat(TitleFormat);
		editor->append(tr("Liste des fournisseurs")+"/n");

		QTextCursor cursor = editor->textCursor();
		cursor.beginEditBlock();
		QTextTableFormat tableFormat;  
		tableFormat.setAlignment(Qt::AlignHCenter);  
		tableFormat.setAlignment(Qt::AlignLeft);  
		tableFormat.setBackground(QColor("#ffffff"));  
		tableFormat.setCellSpacing(5);
		tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_None);

		QSqlQuery req;
		req.exec("SELECT COUNT(*) FROM Fournisseur WHERE supprime=false");
		int count=0;
		if(req.next())
		{
			count=req.value(0).toInt();
		}

		QTextTable * tableau = cursor.insertTable(count, 12, tableFormat);
		QTextFrame *frame = cursor.currentFrame();  
		QTextFrameFormat frameFormat = frame->frameFormat();  
		frameFormat.setBorder(0);  
		frame->setFrameFormat(frameFormat);

		QTextCharFormat format_entete_tableau;
		format_entete_tableau.setFontPointSize(10);  
		format_entete_tableau.setFontWeight(QFont::Bold);

		QTextCharFormat format_cellule;  
		format_cellule.setFontPointSize(8);

		QString titres[] = {"Nom","N TVA","Adresse","Code postal","Localite","Pays","Tl","Fax","e-mail","IBAN","BIC","Banque"};
		for(int i=0;i<12;i++)
		{
			QTextTableCell titre = tableau->cellAt(0,i);
			QTextCursor cellCursor = titre.firstCursorPosition();
			cellCursor.insertText(titres[i],format_entete_tableau);
		}

		QTextTableCell cell;  
		QTextCursor cellCursor;

		req.exec("SELECT * FROM Fournisseur WHERE supprime=FALSE");
		for (int row = 1; row < count; row ++) 
		{
			if(req.next())
			{
				for (int col = 0; col < 12; col ++)  
				{  
					cell = tableau->cellAt(row,col);  
					cellCursor = cell.firstCursorPosition();  
					cellCursor.insertText(req.value(col+1).toString(),format_cellule);  
				}
			}
		}

		editor->print(printer);
	}
}
FenPrincipale::~FenPrincipale()
{
	if(currentWidget)
	{
		delete currentWidget;
		currentWidget=0;
	}
	delete ui;
}
void FenPrincipale::OuvrirVente()
{
	SetWidget(new FenVente());
}
void FenPrincipale::OuvrirCaisse()
{
	SetWidget(new FenCaisse());
}
void FenPrincipale::SetWidget(QWidget* widget)
{
	setCentralWidget(widget);
	if(currentWidget!=0)
	{
		delete currentWidget;
		currentWidget=0;
	}
	currentWidget=widget;
}
void FenPrincipale::OuvrirIntroClient()
{
	FenIntroClient intro;
	intro.exec();
}
void FenPrincipale::OuvrirIntroCaisse()
{
	FenACaisse intro;
	if(intro.exec()==QDialog::Accepted)
		intro.validate();
}
void FenPrincipale::OuvrirJournalVente()
{
	SetWidget(new FenJournalVente());
}
void FenPrincipale::ImprimerJournalVente()
{
	FenIntrodate fen;
	if(fen.exec()!=QDialog::Accepted)
	{
		return;
	}
	QPrinter * printer = new QPrinter(QPrinter::HighResolution);
	printer->setPaperSize (QPrinter::A4);
	printer->setOutputFormat (QPrinter::NativeFormat);
	printer->setOrientation(QPrinter::Portrait);  
	printer->setFullPage(true);
	QPrintDialog printDialog(printer,this);
	if(printDialog.exec()==QDialog::Accepted)
	{
		QTextCharFormat NormalFormat;
		QTextCharFormat ItalicFormat;
		ItalicFormat.setFontItalic(true);
		QTextCharFormat TitleFormat;
		TitleFormat.setFontPointSize(15);
		TitleFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
		TitleFormat.setFontWeight(QFont::Bold);
		TitleFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
		QTextBrowser* editor = new QTextBrowser;
		QDate date = QDate::currentDate();
		QTime heure = QTime::currentTime();
		editor->setAlignment(Qt::AlignLeft);
		editor->setCurrentCharFormat(ItalicFormat);
		editor->append(date.toString("dddd dd MMMM yyyy")+" "+heure.toString("hh:mm:ss")+"/n");
		editor->setAlignment(Qt::AlignCenter);
		editor->setCurrentCharFormat(TitleFormat);
		editor->append(tr("Journal des ventes")+"/n");

		QTextCursor cursor = editor->textCursor();
		cursor.beginEditBlock();
		QTextTableFormat tableFormat;  
		tableFormat.setAlignment(Qt::AlignHCenter);  
		tableFormat.setAlignment(Qt::AlignLeft);  
		tableFormat.setBackground(QColor("#ffffff"));
		tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_None);
		tableFormat.setCellSpacing(5);

		QSqlQuery req;
		req.prepare("SELECT COUNT(*) FROM Ticket WHERE DATE(date)>=:date1 AND DATE(date)<=:date2 ORDER BY DATE(date),num");
		req.bindValue(":date1",fen.PreDate());
		req.bindValue(":date2",fen.SecDate());
		req.exec();
		int count=0;
		if(req.next())
		{
			count=req.value(0).toInt();
		}
		else
		{
			QMessageBox::critical(0,"Erreur","Aucun ticket  imprimer trouv");
			return;
		}
		if(count==0)
		{
			QMessageBox::critical(0,"Erreur","Aucun ticket  imprimer trouv");
			return;
		}
		QTextTable * tableau = cursor.insertTable(count+1, 5, tableFormat);
		QTextFrame *frame = cursor.currentFrame();  
		QTextFrameFormat frameFormat = frame->frameFormat();  
		frameFormat.setBorder(0);  
		frame->setFrameFormat(frameFormat);

		QTextCharFormat format_entete_tableau;
		format_entete_tableau.setFontPointSize(10);  
		format_entete_tableau.setFontWeight(QFont::Bold);

		QTextCharFormat format_cellule;  
		format_cellule.setFontPointSize(8);

		QString titres[] = {"N","Date","Caisse","Banque","Bons/chques"};
		for(int i=0;i<5;i++)
		{
			QTextTableCell titre = tableau->cellAt(0,i);
			QTextCursor cellCursor = titre.firstCursorPosition();
			cellCursor.insertText(titres[i],format_entete_tableau);
		}

		QTextTableCell cell;  
		QTextCursor cellCursor;

		req.prepare("SELECT num,DATE_FORMAT(date, '%d/%m/%Y %H:%i:%s'),prixc,prixb,prixd,Nom FROM Client,Ticket WHERE client.id=client AND DATE(date)>=:date1 AND DATE(date)<=:date2  ORDER BY DATE(date),num");
		req.bindValue(":date1",fen.PreDate());
		req.bindValue(":date2",fen.SecDate());
		req.exec();
		for (int row = 1; row < count+1; row ++) 
		{
			if(req.next())
			{
				for (int col = 0; col < 5; col ++)  
				{  
					cell = tableau->cellAt(row,col);
					cellCursor = cell.firstCursorPosition();
					cellCursor.insertText(req.value(col).toString(),format_cellule);
				}
			}
		}
		editor->print(printer);
	}
}
void FenPrincipale::ImprimerTotalJournalVente()
{
	FenIntrodate fen;
	if(fen.exec()!=QDialog::Accepted)
	{
		return;
	}
	QPrinter * printer = new QPrinter(QPrinter::HighResolution);
	printer->setPaperSize (QPrinter::A4);
	printer->setOutputFormat (QPrinter::NativeFormat);
	printer->setOrientation(QPrinter::Portrait);  
	printer->setFullPage(true);
	QPrintDialog printDialog(printer,this);
	if(printDialog.exec()==QDialog::Accepted)
	{
		QTextCharFormat NormalFormat;
		QTextCharFormat ItalicFormat;
		ItalicFormat.setFontItalic(true);
		QTextCharFormat TitleFormat;
		TitleFormat.setFontPointSize(15);
		TitleFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
		TitleFormat.setFontWeight(QFont::Bold);
		TitleFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
		QTextBrowser* editor = new QTextBrowser;
		QDate date = QDate::currentDate();
		QTime heure = QTime::currentTime();
		editor->setAlignment(Qt::AlignLeft);
		editor->setCurrentCharFormat(ItalicFormat);
		editor->append(date.toString("dddd dd MMMM yyyy")+" "+heure.toString("hh:mm:ss")+"/n");
		editor->setAlignment(Qt::AlignCenter);
		editor->setCurrentCharFormat(TitleFormat);
		editor->append(tr("Total du journal des ventes")+"/n");

		QTextCursor cursor = editor->textCursor();
		cursor.beginEditBlock();
		QTextTableFormat tableFormat;  
		tableFormat.setAlignment(Qt::AlignHCenter);  
		tableFormat.setAlignment(Qt::AlignLeft);  
		tableFormat.setBackground(QColor("#ffffff"));  
		tableFormat.setCellSpacing(5);
		tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_None);

		QSqlQuery req;
		req.prepare("SELECT COUNT(DISTINCT DATE(date)) FROM Ticket WHERE DATE(date)>=:date1 AND DATE(date)<=:date2");
		req.bindValue(":date1",fen.PreDate());
		req.bindValue(":date2",fen.SecDate());
		req.exec();
		int count=0;
		if(req.next())
		{
			count=req.value(0).toInt();
		}
		else
		{
			QMessageBox::critical(0,"Erreur","Aucun ticket à imprimer trouvé");
			return;
		}
		if(count==0)
		{
			QMessageBox::critical(0,"Erreur","Aucun ticket à imprimer trouvé");
			return;
		}
		QTextTable * tableau = cursor.insertTable(count+2, 6, tableFormat);
		QTextFrame *frame = cursor.currentFrame();  
		QTextFrameFormat frameFormat = frame->frameFormat();  
		frameFormat.setBorder(0);  
		frame->setFrameFormat(frameFormat);

		QTextCharFormat format_entete_tableau;
		format_entete_tableau.setFontPointSize(10);  
		format_entete_tableau.setFontWeight(QFont::Bold);

		QTextCharFormat format_cellule;  
		format_cellule.setFontPointSize(8);

		QString titres[] = {"Date"," Total caisse","Total banque","Total bons/chêques","Total général"};
		for(int i=0;i<5;i++)
		{
			QTextTableCell titre = tableau->cellAt(0,i);
			QTextCursor cellCursor = titre.firstCursorPosition();
			cellCursor.insertText(titres[i],format_entete_tableau);
		}

		QTextTableCell cell;
		QTextCursor cellCursor;

		req.prepare("SELECT date,prixc,prixb,prixd FROM Ticket WHERE DATE(date)>=:date1 AND DATE(date)<=:date2 ORDER BY date,num");
		req.bindValue(":date1",fen.PreDate());
		req.bindValue(":date2",fen.SecDate());
		req.exec();
		if(!req.next())
		{
			return;
		}
		QDate datecalc(req.value(0).toDate());
		double pba=0.,pca=0.,pbo=0.;
		int co=1;
		do
		{
			if(req.value(0).toDate()!=datecalc)
			{
				cell = tableau->cellAt(co,0);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(datecalc.toString(),format_cellule);
				cell = tableau->cellAt(co,1);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(QString("%1").arg(pca),format_cellule);
				cell = tableau->cellAt(co,2);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(QString("%1").arg(pba),format_cellule);
				cell = tableau->cellAt(co,3);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(QString("%1").arg(pbo),format_cellule);
				cell = tableau->cellAt(co,4);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(QString("%1").arg(pca+pba+pbo),format_cellule);
				pba=pca=pbo=0.;
				co++;
				datecalc=req.value(0).toDate();
			}
			pca+=req.value(1).toDouble();
			pbo+=req.value(3).toDouble();
			pba+=req.value(2).toDouble();
		}while(req.next());
		cell = tableau->cellAt(co,0);
		cellCursor = cell.firstCursorPosition();
		cellCursor.insertText(datecalc.toString(),format_cellule);
		cell = tableau->cellAt(co,1);
		cellCursor = cell.firstCursorPosition();
		cellCursor.insertText(QString("%1").arg(pca),format_cellule);
		cell = tableau->cellAt(co,2);
		cellCursor = cell.firstCursorPosition();
		cellCursor.insertText(QString("%1").arg(pba),format_cellule);
		cell = tableau->cellAt(co,3);
		cellCursor = cell.firstCursorPosition();
		cellCursor.insertText(QString("%1").arg(pbo),format_cellule);
		cell = tableau->cellAt(co,4);
		cellCursor = cell.firstCursorPosition();
		cellCursor.insertText(QString("%1").arg(pca+pba+pbo),format_cellule);
		editor->print(printer);
	}
}
void FenPrincipale::ImprimerJournalCaisse()
{
	FenIntrodate fen;
	if(fen.exec()!=QDialog::Accepted)
	{
		return;
	}
	QPrinter * printer = new QPrinter(QPrinter::HighResolution);
	printer->setPaperSize (QPrinter::A4);
	printer->setOutputFormat (QPrinter::NativeFormat);
	printer->setOrientation(QPrinter::Portrait);  
	printer->setFullPage(true);
	QPrintDialog printDialog(printer,this);
	if(printDialog.exec()==QDialog::Accepted)
	{
		QTextCharFormat NormalFormat;
		QTextCharFormat ItalicFormat;
		ItalicFormat.setFontItalic(true);
		QTextCharFormat TitleFormat;
		TitleFormat.setFontPointSize(15);
		TitleFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
		TitleFormat.setFontWeight(QFont::Bold);
		TitleFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
		QTextBrowser* editor = new QTextBrowser;
		QDate date = QDate::currentDate();
		QTime heure = QTime::currentTime();
		editor->setAlignment(Qt::AlignLeft);
		editor->setCurrentCharFormat(ItalicFormat);
		editor->append(date.toString("dddd dd MMMM yyyy")+" "+heure.toString("hh:mm:ss")+"/n");
		editor->setAlignment(Qt::AlignCenter);
		editor->setCurrentCharFormat(TitleFormat);
		editor->append(tr("Journal de caisse")+"/n");

		QTextCursor cursor = editor->textCursor();
		cursor.beginEditBlock();
		QTextTableFormat tableFormat;  
		tableFormat.setAlignment(Qt::AlignHCenter);  
		tableFormat.setAlignment(Qt::AlignLeft);  
		tableFormat.setBackground(QColor("#ffffff"));  
		tableFormat.setCellSpacing(5);
		tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_None);
		int count=0;

		QSqlQuery req;
		req.prepare("SELECT COUNT(*) FROM Ticket WHERE DATE(date)>=:date1 AND DATE(date)<=:date2 AND prixc!=0");
		req.bindValue(":date1",fen.PreDate());
		req.bindValue(":date2",fen.SecDate());
		req.exec();
		if(req.next())
		{
			count+=req.value(0).toInt();
		}
		req.prepare("SELECT COUNT(*) FROM Facture WHERE DATE(date)>=:date1 AND DATE(date)<=:date2 AND statut=2");
		req.bindValue(":date1",fen.PreDate());
		req.bindValue(":date2",fen.SecDate());
		req.exec();
		if(req.next())
		{
			count+=req.value(0).toInt();
		}
		req.prepare("SELECT COUNT(*) FROM Caisse WHERE DATE(date)>=:date1 AND DATE(date)<=:date2");
		req.bindValue(":date1",fen.PreDate());
		req.bindValue(":date2",fen.SecDate());
		req.exec();
		if(req.next())
		{
			count+=req.value(0).toInt();
		}
		QTextTable * tableau = cursor.insertTable(count+2, 5, tableFormat);
		QTextFrame *frame = cursor.currentFrame();  
		QTextFrameFormat frameFormat = frame->frameFormat();  
		frameFormat.setBorder(0);  
		frame->setFrameFormat(frameFormat);

		QTextCharFormat format_entete_tableau;
		format_entete_tableau.setFontPointSize(10);  
		format_entete_tableau.setFontWeight(QFont::Bold);

		QTextCharFormat format_cellule;  
		format_cellule.setFontPointSize(8);

		QString titres[] = {"Date"," Dnomination","Sortie","Entre","Solde"};
		for(int i=0;i<5;i++)
		{
			QTextTableCell titre = tableau->cellAt(0,i);
			QTextCursor cellCursor = titre.firstCursorPosition();
			cellCursor.insertText(titres[i],format_entete_tableau);
		}

		QTextTableCell cell;
		QTextCursor cellCursor;

		req.prepare("CALL calculsolde(:date)");
		req.bindValue(":date",fen.PreDate().addDays(-1));
		req.exec();
		double solde;
		if(req.next())
		{
			cell = tableau->cellAt(1,0);
			cellCursor = cell.firstCursorPosition();
			cellCursor.insertText(fen.PreDate().toString("dd/MM/yyyy"),format_cellule);
			cell = tableau->cellAt(1,4);
			cellCursor = cell.firstCursorPosition();
			cellCursor.insertText(QString::number(req.value(0).toDouble(),'f',2),format_cellule);
			solde=req.value(0).toDouble();
		}
		QDate date1,date2;
		date1=fen.PreDate();
		date2=fen.SecDate();
		int co=2;
		while(date1<=date2)
		{
			req.prepare("SELECT num,prixc FROM Ticket WHERE DATE(date)=:date AND prixc!=0");
			req.bindValue(":date",date1);
			req.exec();
			while(req.next())
			{
				cell = tableau->cellAt(co,0);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(date1.toString("dd/MM/yyyy"),format_cellule);
				cell = tableau->cellAt(co,1);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(QString("Ticket n %1").arg(req.value(0).toInt()),format_cellule);
				cell = tableau->cellAt(co,3);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(QString::number(req.value(1).toDouble(),'f',2),format_cellule);
				cell = tableau->cellAt(co,4);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(QString::number(solde+=req.value(1).toDouble(),'f',2),format_cellule);
				co++;
			}
			req.prepare("SELECT montant,nbdoc FROM Facture WHERE datepai=:date AND statut=2");
			req.bindValue(":date",date1);
			req.exec();
			while(req.next())
			{
				cell = tableau->cellAt(co,0);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(date1.toString("dd/MM/yyyy"),format_cellule);
				cell = tableau->cellAt(co,1);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(QString("Facture n %1").arg(req.value(1).toString()),format_cellule);
				cell = tableau->cellAt(co,2);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(QString::number(req.value(0).toDouble(),'f',2),format_cellule);
				cell = tableau->cellAt(co,4);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(QString::number(solde-=req.value(0).toDouble(),'f',2),format_cellule);
				co++;
			}
			req.prepare("SELECT montant,nom FROM Caisse WHERE DATE(date)=:date");
			req.bindValue(":date",date1);
			req.exec();
			while(req.next())
			{
				cell = tableau->cellAt(co,0);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(date1.toString("dd/MM/yyyy"),format_cellule);
				cell = tableau->cellAt(co,1);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(QString("Mouvement caisse : %1").arg(req.value(1).toString()),format_cellule);
				if(req.value(0).toDouble()<0)
				{
					cell = tableau->cellAt(co,2);
					cellCursor = cell.firstCursorPosition();
					cellCursor.insertText(QString::number(-req.value(0).toDouble(),'f',2),format_cellule);
				}
				else
				{
					cell = tableau->cellAt(co,3);
					cellCursor = cell.firstCursorPosition();
					cellCursor.insertText(QString::number(req.value(0).toDouble(),'f',2),format_cellule);
				}
				cell = tableau->cellAt(co,4);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(QString::number(solde+=req.value(0).toDouble(),'f',2),format_cellule);
				co++;
			}

			date1=date1.addDays(1);
		}
		editor->print(printer);
	}
}
void FenPrincipale::OuvrirClient()
{
	SetWidget(new FenClient());
}
void FenPrincipale::ImprimerClient()
{
	QPrinter * printer = new QPrinter(QPrinter::HighResolution);
	printer->setPaperSize (QPrinter::A4);
	printer->setOutputFormat (QPrinter::NativeFormat);
	printer->setOrientation(QPrinter::Portrait);  
	printer->setFullPage(true);
	QPrintDialog printDialog(printer,this);
	if(printDialog.exec()==QDialog::Accepted)
	{
		QTextCharFormat NormalFormat;
		QTextCharFormat ItalicFormat;
		ItalicFormat.setFontItalic(true);
		QTextCharFormat TitleFormat;
		TitleFormat.setFontPointSize(15);
		TitleFormat.setUnderlineStyle(QTextCharFormat::SingleUnderline);
		TitleFormat.setFontWeight(QFont::Bold);
		TitleFormat.setVerticalAlignment(QTextCharFormat::AlignMiddle);
		QTextBrowser* editor = new QTextBrowser;
		QDate date = QDate::currentDate();
		QTime heure = QTime::currentTime();
		editor->setAlignment(Qt::AlignLeft);
		editor->setCurrentCharFormat(ItalicFormat);
		editor->append(date.toString("dddd dd MMMM yyyy")+" "+heure.toString("hh:mm:ss")+"/n");
		editor->setAlignment(Qt::AlignCenter);
		editor->setCurrentCharFormat(TitleFormat);
		editor->append(tr("Liste des clients")+"/n");

		QTextCursor cursor = editor->textCursor();
		cursor.beginEditBlock();
		QTextTableFormat tableFormat;  
		tableFormat.setAlignment(Qt::AlignHCenter);  
		tableFormat.setAlignment(Qt::AlignLeft);  
		tableFormat.setBackground(QColor("#ffffff"));  
		tableFormat.setCellSpacing(5);
		tableFormat.setBorderStyle(QTextFrameFormat::BorderStyle_None);
		int count=0;
		QSqlQuery req;
		req.exec("SELECT COUNT(*) FROM Client");
		if(req.next())
		{
			count=req.value(0).toInt();
		}
		QTextTable * tableau = cursor.insertTable(count+2, 5, tableFormat);
		QTextFrame *frame = cursor.currentFrame();  
		QTextFrameFormat frameFormat = frame->frameFormat();  
		frameFormat.setBorder(0);  
		frame->setFrameFormat(frameFormat);

		QTextCharFormat format_entete_tableau;
		format_entete_tableau.setFontPointSize(10);  
		format_entete_tableau.setFontWeight(QFont::Bold);

		QTextCharFormat format_cellule;  
		format_cellule.setFontPointSize(8);

		QString titres[] = {"Nom","Prnom","Adresse","Code postal","Localit"};
		for(int i=0;i<5;i++)
		{
			QTextTableCell titre = tableau->cellAt(0,i);
			QTextCursor cellCursor = titre.firstCursorPosition();
			cellCursor.insertText(titres[i],format_entete_tableau);
		}

		QTextTableCell cell;
		QTextCursor cellCursor;
		int co=1;
		req.exec("SELECT nom,prenom,adresse,codepostal,localite FROM Client ORDER BY nom,prenom,adresse");
		while(req.next())
		{
			for(int i=0;i<5;i++)
			{
				cell = tableau->cellAt(co,i);
				cellCursor = cell.firstCursorPosition();
				cellCursor.insertText(req.value(i).toString());
			}
			co++;
		}
		editor->print(printer);
	}
}
void FenPrincipale::OuvrirIntroFacture()
{
	SetWidget(new FenIntroFacture());
}
