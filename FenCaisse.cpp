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



#include "FenCaisse.h"
#include <QtSql/QtSql>
#include "ui_CaisseWindow.h"
FenCaisse::FenCaisse()
{
	ui = new Ui::CaisseWindow();
	ui->setupUi(this);
	QSqlQuery req;
	req.exec("CALL CalculSolde(CURDATE())");
	if(!req.next())
	{
		QMessageBox::critical(this,"Erreur","Dfaillance gnrale du systme.<br/>Contacter une personne responsable");
		return;
	}
	ui->doubleSpinBox->setValue(req.value(0).toDouble());
}
FenCaisse::~FenCaisse(void)
{
	delete ui;
}
