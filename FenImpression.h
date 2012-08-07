#ifndef DIALOGIMPRESSION_H
#define DIALOGIMPRESSION_H

#include <QDialog>

namespace Ui {
class DialogImpression;
}

class DialogImpression : public QDialog
{
    Q_OBJECT
    
public:
    explicit DialogImpression(QWidget *parent = 0);
    ~DialogImpression();
    
private:
    Ui::DialogImpression *ui;
};

#endif // DIALOGIMPRESSION_H
