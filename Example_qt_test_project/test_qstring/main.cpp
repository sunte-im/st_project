#include <QCoreApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
#if 0
    QString str = "Hello";
    QString str2("Hello");
    QString str3{"Hello"};


///
    // 0x0055 : U
    // 0x006e : n
    static const QChar data[4] = { 0x0055, 0x006e, 'U', 'n' };
    QString str1(data, 4);
    qDebug() << str1; // result : UnUn


    // 0x0041 : A
    // 0x0042 : B
    QString str;
    str.resize(4);
    str[0] = QChar('A');
    str[1] = QChar('B');
    str[2] = QChar(0x0041);
    str[3] = QChar(0x0042);
    qDebug() << str;  // result : ABAB


///
    int q = QString::compare("AbCd", "abcd", Qt::CaseSensitive);    // q != 0
    int x = QString::compare("AbCd", "abcd", Qt::CaseInsensitive);  // x == 0
    int y = QString::compare("auto", "Car", Qt::CaseSensitive);     // y > 0
    int z = QString::compare("auto", "Car", Qt::CaseInsensitive);   // z < 0

    qDebug() << q << x << y << z;       // result : -32 0 30 -2


///
    QString str = "and";
    str.prepend("Black ");     // str == "Black and"
    str.append(" White");      // str == "Black and White"
    qDebug() << str;        // result : Black and white
    str.replace(6, 3, "&");    // str == "Black & White"
    qDebug() << str;        // result : Black & white


///
    int n = 10;
    QString intToStr = QString::number(n);

    QString str = "20";
    int strToInt = str.toInt();




///
    QString str = "abcdefg";

    int size = str.size();
    // result : 7

    int count = str.count();
    // result : 7

    int length = str.length();
    // result : 7



///
    QString addr = "192.168.0.1";

    QStringList list = addr.split(".");
    // result : "192", "168", "0", "1"



    QString str = "Pineapple";
    QString a = str.first(4);       // a == "Pine"
    QString b = str.last(5);        // b == "apple"
    QChar c = str.at(3);            // c == "e"



///

    QString str = "I Don't know.";

    bool b = str.contains("don't", Qt::CaseInsensitive); // 대소문자 구분 없이
    qDebug() << __FUNCTION__ << b;
    // b : true



///
    QString str = "I Don't know.";
    int n = str.indexOf("know", Qt::CaseInsensitive);
    // n : 8
    index = str.indexOf("dott", Qt::CaseInsensitive);
    // n : -1


///
    QString addr("7W-B5-6C-B6-12-8A");
    addr.replace("-", ":");
    // result : 7W:B5:6C:B6:12:8A



///

    QString str("I am a boy.");
    QString str1("girl");

    str.replace(7, 3, str1);
    // result : I am a girl.




///
    QString str1 = "TEST";
    QString str2 = "test";
    QString str3 = "Test";

    bool isUpper = str1.isUpper();      // true
    bool isLower = str2.isLower();      // true
    bool isLower2 = str3.isLower();     // false
    str1 = str1.toLower(); // str1 == str2
    qDebug() << str1 << str2 << str3;
#else
#endif
    return a.exec();
}
