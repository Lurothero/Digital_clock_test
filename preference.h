#ifndef PREFERENCE_H
#define PREFERENCE_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class Preference;
}

class Preference : public QDialog
{
    Q_OBJECT

public:
    //Constructors
    explicit Preference(QWidget *parent = nullptr);
    ~Preference();

private:
    //Private datamembers
    Ui::Preference *ui;
    QButtonGroup  *radio_timeFormat;



private slots:
    //Customs slots
    void onAccepted();


};

#endif // PREFERENCE_H
