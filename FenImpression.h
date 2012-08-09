#ifndef FenImpression_H
#define FenImpression_H

#include <QDialog>

namespace Ui {
class DialogImpression;
}

class FenImpression : public QDialog
{
    Q_OBJECT
    
public:
    explicit FenImpression(QWidget *parent = 0);
    ~FenImpression();
    
private:
    Ui::DialogImpression *ui;

public slots:
    void imprimer();
};

#endif // FenImpression_H
