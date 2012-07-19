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



#ifndef FENSQL_H
#define FENSQL_H
#include <QtSql/QtSql>
#include <QtGui/qmainwindow.h>
namespace Ui {
    class Form;
}

class FenSQL : public QWidget
{
Q_OBJECT
public:
    explicit FenSQL(QWidget *parent = 0);
    ~FenSQL();
private slots:
	void changementArticle(const QModelIndex &index);
private:
	QSqlRelationalTableModel* modelArticle;
	QSqlRelationalTableModel* modelChapitre;
	Ui::Form *ui;
};

#endif
