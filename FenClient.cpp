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



#include "FenClient.h"
#include "ui_ClientWindow.h"
#include "FenVente.h"
#include <set>
FenClient::FenClient(void)
{
	ui= new Ui::GesClient();
	ui->setupUi(this);
	ui->tableView->setModel(&model);

    model.setTable("client");
	model.setSort(1,Qt::AscendingOrder);
	model.select();

	ui->tableView->setColumnHidden(0, true);
	ui->tableView->setColumnHidden(3, true);
	ui->tableView->resizeColumnsToContents();

	connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(BoutonSupprimer()));
}
FenClient::~FenClient(void)
{
	delete ui;
}
void FenClient::BoutonSupprimer()
{
	QItemSelectionModel *selection = ui->tableView->selectionModel();
	QModelIndexList listeSelections = selection->selectedIndexes();
	std::set<int,invless<int> > list;
	for(int i=0,c=listeSelections.size();i<c;i++)
	{
		int numligne =listeSelections[i].row();
		list.insert(numligne);
	}
	for(std::set<int,invless<int> >::iterator it = list.begin();it!=list.end();it++)
	{
		model.removeRow(*it);
	}
	model.submitAll();
}
