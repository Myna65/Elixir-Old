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



#include <QtGui/QtGui>
#include <QtSql/QtSql>
#include "FenPayement.h"
namespace Ui
{
	class VenteWindow;
}
template<typename T> struct invless
{
	bool operator()(const T& lhs,const T& rhs) const
	{
		return (lhs>rhs);
	}
};
class FenVente : public QWidget
{
	Q_OBJECT
public:
	FenVente();
	~FenVente();
private slots:
	void BoutonValider();
	void BoutonCode();
	void BoutonTEffacer();
	void BoutonSEffacer();
	void ClientChange(int current);
	void DeduireAcompte();
	void AjouterAcompte();
	void BoutonManuel();
private:
	std::vector<int> clients;
	int curclient;
	int listecompte;
	QStandardItemModel* liste;
	Ui::VenteWindow* ui;
	QSqlTableModel* model;
};

