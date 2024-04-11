#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDateTime now = QDateTime::currentDateTime();
    QDateTime xmas(QDate(now.date().year(), 12, 25).startOfDay());
    qDebug("There are %d seconds to Christmas", now.secsTo(xmas));

    return a.exec();
}
