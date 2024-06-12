#include <QCoreApplication>
#include "manager/AppManager.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    AppManager app;
    return a.exec();
}
