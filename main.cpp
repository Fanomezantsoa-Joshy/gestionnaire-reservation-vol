#include "admin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    admin w;
    w.showMaximized();
    return a.exec();
}
