#include "mainwidget.h"
#include <QApplication>
#include "creationfichierconfigurationdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget m;
    return a.exec();
}
