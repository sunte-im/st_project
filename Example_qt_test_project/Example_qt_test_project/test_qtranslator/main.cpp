#include "dialog.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load(":/language/ko_KR.qm");
    a.installTranslator(&translator);

    Dialog w;
    w.show();
    return a.exec();
}
