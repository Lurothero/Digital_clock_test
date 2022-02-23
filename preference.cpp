#include "preference.h"
#include "ui_preference.h"

#include <QDebug>
#include <QSettings>

Preference::Preference(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Preference)
{
    ui->setupUi(this);

    //setting up dialouge settings
    QSettings settings;

    //Set the 24h radio button to be selected,Prevents crashing due to no button selected on accept
    ui->radio_24h->setChecked(true);

    //Set the position of the last used color value
    ui->colorBox->setCurrentIndex(settings.value("Color").toInt());

    //connect preference OK button to perform a custom slot function
    connect(ui->buttonBox ,SIGNAL(accepted()),this,SLOT(onAccepted()));


}

Preference::~Preference()
{
    delete ui;
}

void Preference::onAccepted()
{


       //Create a setting object
       QSettings settings("CMPS2212 GUI Programming", "Rene Robert Allen and Luigi Acuna Digital Clock");

       //save the last color index
       settings.setValue("Color", ui->colorBox->currentIndex());




       //Create a dynamic button group and add existing radio buttons
       radio_timeFormat = new QButtonGroup ;
       radio_timeFormat->addButton(ui->radio_12h);
       radio_timeFormat->addButton(ui->radio_24h);

       //save the last format used
       settings.setValue("Format",radio_timeFormat->checkedButton()->objectName());


       //DEBUGGING PURPOSES
       qDebug() << "WHATS MY VALUE?? : " << radio_timeFormat->checkedButton()->objectName();
}


