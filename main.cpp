#include "renerobertallenandluigiacunadigiclock.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    QCoreApplication::setApplicationName("Rene Robert Allen and Luigi Acuna Digital Clock");
    QCoreApplication::setOrganizationName("CMPS2212 GUI Programming");


    //Create a clock window
    ReneRobertAllenAndLuigiAcunaDigiClock w;
    w.show();

    return a.exec();
}
