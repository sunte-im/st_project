#include "dialog.h"
#include "ui_dialog.h"
#include "AES.cpp"
#include <QNetworkInterface>
#include <QDate>
#include <QStandardPaths>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

#define AES_CIPHER_KEY "KEY_12345_ABC"
QString aes_encryption(QString str)
{
    AES aes128(128);
    QByteArray ba = str.toUtf8().toBase64();
    std::string _str =  QString::fromUtf8(ba).toStdString(); // input text
    std::string hexStr = aes128.convertStrToHexStr(_str);    // convert to hex input text
    std::string cipherKey = AES_CIPHER_KEY;                  // cipherKey
    std::string convertCipherKey = aes128.convertStrToHexStr(cipherKey);        // convert to hex cipherKey
    std::string encryptText = aes128.encryption(hexStr, convertCipherKey);      // encryption
    return QString::fromStdString(encryptText);
}

QString aes_decryption(QString str)
{
    AES aes128(128);
    std::string _str = str.toStdString();                    // input text(hex)
    std::string cipherKey = AES_CIPHER_KEY;                  // cipherKey
    std::string convertCipherKey = aes128.convertStrToHexStr(cipherKey);        // convert to hex cipherKey
    std::string decryptText = aes128.decryption(_str, convertCipherKey);        // decryption
    std::string convertDecryptText = aes128.convertHexStrToStr(decryptText);    // convert to text
    QString rtnStr = QString::fromStdString(convertDecryptText);
    QByteArray ba = QByteArray::fromBase64(rtnStr.toUtf8());
    return QString::fromUtf8(ba);
}

QString getMacAddress()
{
    foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
    {
        // Return only the first non-loopback MAC Address
        if (!(netInterface.flags() & QNetworkInterface::IsLoopBack))
            return netInterface.hardwareAddress();
    }
    return QString();
}

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    ui->dateEdit_createDate->setDate(QDate::currentDate());
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_getMac_clicked()
{
    qDebug() << __FUNCTION__ << getMacAddress();
    ui->lineEdit_macAddr->setText(getMacAddress());
}

void Dialog::on_pushButton_import_mac_clicked()
{
    QString _path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Open key file",
                                                    _path,
                                                    "key file(*.ekey)",
                                                    Q_NULLPTR,
                                                    QFileDialog::ShowDirsOnly);

    if (fileName.isEmpty())
        return;

    qDebug() << __FUNCTION__ << fileName;
    QString en_text;
    QFile file(fileName);
    if (file.open(QFile::ReadWrite | QFile::Text))
    {
        QTextStream in(&file);
        en_text = in.readLine();
        file.close();
    }

    qDebug() << __FUNCTION__ << en_text;

    QString de_text = aes_decryption(en_text);
    //QString macAddr = de_text.left(12);
    //qDebug() << __FUNCTION__ << de_text << macAddr;
    ui->lineEdit_import_mac->setText(de_text);
}

void Dialog::on_pushButton_createKey_clicked()
{
    QString macAddr = ui->lineEdit_createMacAddr->text();
    if (macAddr.isEmpty())
    {
        QMessageBox::information(this, "", "Please enter Mac address.");
        return;
    }

    // export key
    QString _path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString fileName = QFileDialog::getSaveFileName(this, "Export file",
                                                    _path + "/lc.ikey",
                                                    "key file (*.ikey)");
    qDebug() << __FUNCTION__ << fileName;

    if (fileName.isEmpty())
        return;

    qDebug() << __FUNCTION__ << "mac: " << macAddr;
    macAddr = macAddr.replace("-", "");
    macAddr = macAddr.replace("_", "");
    macAddr = macAddr.replace(":", "");
    macAddr = macAddr.replace(".", "");
    qDebug() << __FUNCTION__ << "mac.. : " << macAddr;
    QString dateStr = ui->dateEdit_createDate->date().toString("yyyyMMdd");
    qDebug() << __FUNCTION__ << "dateStr : " << dateStr;
    QString sumText = macAddr + dateStr;
    sumText = aes_encryption(sumText);

    QFile file(fileName);
    if (file.open(QFile::ReadWrite | QFile::Text))
    {
        QTextStream SaveFile(&file);
        SaveFile << sumText;
        file.close();
    }

    QMessageBox::information(this, "", "completed");
}
