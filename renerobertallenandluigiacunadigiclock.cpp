#include "preference.h"
#include "renerobertallenandluigiacunadigiclock.h"
#include "ui_renerobertallendigiclock.h"

#include <QTime>
#include <QTimer>
#include <QString>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QPalette>

#include <QSettings>


ReneRobertAllenAndLuigiAcunaDigiClock::ReneRobertAllenAndLuigiAcunaDigiClock(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ReneRobertAllenDigiClock)
{
    ui->setupUi(this);


    //Dynamically create a timer object
    QTimer *timer = new QTimer;

    //A settings object used to get our last position and size
    QSettings restore_settings;

    //set the color of the lcd display on object creation
    setColor();

    //place clock in prev position
    restoreGeometry(restore_settings.value("MainGeometry").toByteArray());
    restoreState(restore_settings.value("MainState").toByteArray());

    //setting transparent bg
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);


    //DEBUGGING
    qDebug() <<"CREATED DIGICLOCK";

    //Connecting timers
    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));
    //Connecting right click action
    connect(this,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(showContextMenu(const QPoint)));



    //Start the timer with 1sec intervals
    timer->start(1000);

    //Calling updateTime at object creation
    updateTime();


}





ReneRobertAllenAndLuigiAcunaDigiClock::~ReneRobertAllenAndLuigiAcunaDigiClock()
{
    delete ui;
}

void ReneRobertAllenAndLuigiAcunaDigiClock::setColor()
{
    //Variable declaration
    QSettings settings;
    QPalette pal;
    int returnColorIndex = settings.value("Color").toInt();//Get the last saved color from settings

    //Determine color to pass to lcd display
    switch (returnColorIndex){

    //QPalette::Foreground is depreciated, use WindowText
    case 0:
    pal.setColor(QPalette::WindowText, Qt::black);
        break;
    case 1:
        pal.setColor(QPalette::WindowText, Qt::green);
            break;

    case 2:
        pal.setColor(QPalette::WindowText, Qt::red);
            break;

    case 3:
        pal.setColor(QPalette::WindowText, Qt::yellow);
            break;
    }

    //Setting color to display
    ui->lcdNumber->setPalette(pal);

    //apply changes
    this->updateTime();
}



void ReneRobertAllenAndLuigiAcunaDigiClock::mouseReleaseEvent(QMouseEvent *e)
{
    //DEBUGGING
    qDebug() <<"MOUSE CLICKED!";

    //handle mouse event, checks if right mouse was pressed
    if (e->button() == Qt::RightButton) {
    emit customContextMenuRequested(e->pos());
        qDebug() << e->pos();
    }
    else {
    QMainWindow::mouseReleaseEvent(e);
    }
}

void ReneRobertAllenAndLuigiAcunaDigiClock::closeEvent(QCloseEvent *e)
{

    //q settings values modified
    QSettings settings("CMPS2212 GUI Programming", "Rene Robert Allen and Luigi Acuna Digital Clock");


    settings.setValue("MainGeometry", saveGeometry());
    settings.setValue("MainState", saveState());
    settings.setValue("Format","radio_24h");//In reality it would be annoying for a user to have their clock reset to 24H when closing the application.Comment out this line will used the last saved value.

    e->accept();
}


void ReneRobertAllenAndLuigiAcunaDigiClock::mousePressEvent(QMouseEvent *e)
{
    //Getting cursor position and modifying the private QPoint
    m_mousePos = e->pos();

    //DEBUGGING
    qDebug() << "Mouse Vector: " << e;
}

void ReneRobertAllenAndLuigiAcunaDigiClock::mouseMoveEvent(QMouseEvent *e)
{
    //Move the window to the new location
    this->move(e-> globalPosition().toPoint() - m_mousePos);

    //DEBUGGING
    qDebug() << "We are moving";
    qDebug()<< e;
}

void ReneRobertAllenAndLuigiAcunaDigiClock::showPreferences()
{
    //Handles preference UIs
    Preference *pref_window = new Preference(this);

    connect(pref_window,SIGNAL(accepted()),this,SLOT(setColor()));
    pref_window->exec();
    setColor();
}





void ReneRobertAllenAndLuigiAcunaDigiClock::showContextMenu(const QPoint &pos)
{

    //Impliment means construct the function in the respective cpp file...
    QMenu contextMenu;

    //adding what to display in the right click menu
    contextMenu.addAction(QString("Exit"), this, SLOT(close()));
    contextMenu.addAction("Preference", this, SLOT(showPreferences()));
    contextMenu.exec(mapToGlobal(pos));//I would have not gotten this




}

void ReneRobertAllenAndLuigiAcunaDigiClock::updateTime()
{

    qDebug() << "Cycle...Cycle...";

    //Access setting and return the previously saved format
    QString timeFormat = "";

    QSettings settings;
    QString returnFormat = settings.value("Format").toString();

    //DEBUGGING
    qDebug() << "WAS I RETURNED? "<<returnFormat ;

    //Get current system time
    QTime currentTime = QTime::currentTime();



    //get the format based on what was saved, used the buttons name

    if (returnFormat == "radio_12h"){


        timeFormat="h:m:s ap";


    }else if (returnFormat == "radio_24h"){


        timeFormat="hh:mm:ss";

     };

    //saving our time to a format
    QString currentTimeText = currentTime.toString(timeFormat);


    if(currentTime.second() % 2 == 0){

       //Replace the :

       currentTimeText.replace(" ",":");
    }else{
        currentTimeText.replace(":"," ");
    }

    //Apply changes
    ui->lcdNumber->display(currentTimeText);
}

