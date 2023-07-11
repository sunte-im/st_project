#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.addLibraryPath(QCoreApplication::applicationDirPath());
    Dialog w;
    w.show();
    return a.exec();
}
