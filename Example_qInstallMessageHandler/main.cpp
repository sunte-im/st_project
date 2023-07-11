#include "dialog.h"

#include <QApplication>
#include <QDateTime>

void messageOutput(QtMsgType type, const QMessageLogContext& context, const QString &msg)
{
    QString dateTimeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");

    QString typeString;
    switch (type)
    {
    case QtDebugMsg:
        typeString = "[Debug]";
        break;
    case QtWarningMsg:
        typeString = "[Warning]";
        break;
    case QtCriticalMsg:
        typeString = "[Critical]";
        break;
    case QtFatalMsg:
        typeString = "[Fatal]";
        break;
    case QtInfoMsg:
        typeString = "[Info]";
        break;
    default:
        typeString = "[Unknown]";
        break;
    }

    QString _msg = dateTimeStr + " " + typeString +
            "  func: " + context.function +
            //" file: " + context.file +
            "  line: " + QString::number(context.line) +
            "  msg: " + msg;

    fprintf(stderr, "%s\n", qPrintable(_msg));

    fflush(stderr);

}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(messageOutput);

    QApplication a(argc, argv);
    Dialog w;
    w.show();
    return a.exec();
}
