#ifndef FENSQLOPTIONS_H
#define FENSQLOPTIONS_H

#include <QDialog>

namespace Ui {
class FenSqlOptions;
}

class FenSqlOptions : public QDialog
{
    Q_OBJECT
    
public:
    explicit FenSqlOptions(QWidget *parent = 0);
    ~FenSqlOptions();
    
private:
    Ui::FenSqlOptions *ui;
};

#endif // FENSQLOPTIONS_H
