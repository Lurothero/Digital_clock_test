#ifndef RENEROBERTALLENANDLUIGIACUNADIGICLOCK_H
#define RENEROBERTALLENANDLUIGIACUNADIGICLOCK_H

#include <QMainWindow>

#include <QPoint>
#include <QMouseEvent>
#include <QAction>
#include <QMenu>
#include <QColor>


QT_BEGIN_NAMESPACE
namespace Ui { class ReneRobertAllenDigiClock; }
QT_END_NAMESPACE

class ReneRobertAllenAndLuigiAcunaDigiClock : public QMainWindow
{
    Q_OBJECT

public:
    //Contructors
    ReneRobertAllenAndLuigiAcunaDigiClock(QWidget *parent = nullptr);
    ~ReneRobertAllenAndLuigiAcunaDigiClock();

    //Member function
    void setColor();


protected:
    //protected member functions
        void mouseReleaseEvent(QMouseEvent *e);
        void closeEvent(QCloseEvent *e);
        void mousePressEvent(QMouseEvent *);
        void mouseMoveEvent(QMouseEvent *);

private:
     //Private data members
    Ui::ReneRobertAllenDigiClock *ui;
    QPoint m_mousePos;


private slots:

    //custom slots
      void showPreferences();
      void showContextMenu(const QPoint &pos);
      void updateTime();
};
#endif // RENEROBERTALLENANDLUIGIACUNADIGICLOCK_H
