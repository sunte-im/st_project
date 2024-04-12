#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // QTime 사용
    QTime nowTime = QTime::currentTime();
    qDebug() << "nowTime : " << nowTime;
    QTime time2 = nowTime.addSecs(60);    // 60초 추가
    qDebug() << "time2 : " << time2;
    QTime time3 = nowTime.addMSecs(6000);    // 6000 밀리초 (6초) 추가
    qDebug() << "time3 : " << time3;

    QString str1 = nowTime.toString("hh:mmAP");
    qDebug() << str1; // "시:분 AM/PM"


    // QDate 사용
    QDate nowDate = QDate::currentDate();
    qDebug() << "nowDate : " << nowDate;
    QDate date2 = nowDate.addDays(1);    // 1일 추가
    qDebug() << "date2 : " << date2;
    QDate date3 = nowDate.addMonths(1);    // 1달 추가
    qDebug() << "date3 : " << date3;
    QDate date4 = nowDate.addYears(1);    // 1년 추가
    qDebug() << "date4 : " << date4;

    QString str2 = nowDate.toString("'Year': yyyy  /  'Month': MM  /  'Day': dd");
    qDebug() << str2; // "Year: 2024  /  Month: 04  /  Day: 12"

    QDate d1(2024, 3, 17);  // Mar 17, 2024
    QDate d2(2024, 3, 20);  // Mar 20, 2024
    int d3 = d1.daysTo(d2);
    qDebug() << d3; // returns 3
    int d4 = d2.daysTo(d1);
    qDebug() << d4; // returns -3


    // 현재시간날짜
    QDateTime now = QDateTime::currentDateTime();
    qDebug() << "now : " << now;   // 2024-04-11 16:30:40.798
    ///


    // 날짜 시간 포맷 적용
    QString toStr = now.toString("yyyy-MM-dd !! HH:mm:ss.zzz !!!");
    qDebug() << "toStr : " << toStr;
    ///


    // 비교
    QDateTime startDate(QDate(2024, 4, 11), QTime(8, 30, 0));
    QDateTime endDate(QDate(2024, 4, 12), QTime(16, 30, 0));
    qDebug() << "Days from startDate to endDate: " << startDate.daysTo(endDate) << startDate.secsTo(endDate);

    startDate = QDateTime(QDate(2024, 4, 11), QTime(23, 55, 0));
    endDate = QDateTime(QDate(2024, 4, 12), QTime(0, 5, 0));
    qDebug() << "Days from startDate to endDate: " << startDate.daysTo(endDate) << startDate.secsTo(endDate);

    qSwap(startDate, endDate); // Make endDate before startDate.
    qDebug() << "Days from startDate to endDate: " << startDate.daysTo(endDate) << startDate.secsTo(endDate);
    ///


    return a.exec();
}
