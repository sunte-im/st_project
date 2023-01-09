
#include <QApplication>
#include <QtWidgets>
#include <iostream>

#include "sendemail.h"
#include "../SmtpMime/include/SmtpMime"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SendEmail form(NULL);
    form.setWindowTitle("SMTP sendmail demo");
    form.show();
    return a.exec();
}
