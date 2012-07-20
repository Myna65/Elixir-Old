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



#include <QtGui/qapplication.h>
#include <Qt/qtranslator.h>
#include <Qt/qlocale.h>
#include <Qt/qlibraryinfo.h>
#include <QtSql/QtSql>
#include <QtGui/QtGui>
#include "FenPrincipale.h"

int main(int argc, char* argv[])
{
    QApplication app(argc,argv);
	app.addLibraryPath(".");

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("127.0.0.1");
    db.setDatabaseName("Elixir");
    db.setUserName("Elixir_user");
    db.setPassword("");
	if(!db.open())
	{
		QMessageBox::critical(0,"Erreur",db.lastError().text());
	}
    QTranslator translator;
    translator.load("qt_FR",".");
    app.installTranslator(&translator);

    FenPrincipale principale;
    principale.show();

	int ret=app.exec();

	db.close();

	return ret;
}
