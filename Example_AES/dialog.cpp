#include "dialog.h"
#include "ui_dialog.h"
#include "AES.hpp"
#include <QDebug>

//#define CIPHER_KEY "ABC112233dw123ds"
#define AES_CIPHER_KEY "HUVITZ_HUVALLEY_"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_encryption_clicked()
{
    QString lineText = ui->lineEdit_encryption->text();
    QByteArray ba = lineText.toUtf8().toBase64();
    AES aes128(128);
    //std::string str = lineText.toStdString();               // input text
    std::string str =  QString::fromUtf8(ba).toStdString();               // input text
    std::string hexStr = aes128.convertStrToHexStr(str);    // convert to hex input text
    //std::string cipherKey = "HUVITZ_HUVALLEY_";             // cipherKey
    std::string cipherKey = AES_CIPHER_KEY;
    std::string convertCipherKey = aes128.convertStrToHexStr(cipherKey);        // convert to hex cipherKey
    std::string encryptText = aes128.encryption(hexStr, convertCipherKey);      // encryption

    ui->plainTextEdit_encryption->setPlainText(QString::fromStdString(encryptText));
}

void Dialog::on_pushButton_decryption_clicked()
{

    QString lineText = ui->lineEdit_decryption->text();
    AES aes128(128);
    std::string str = lineText.toStdString();           // input text(hex)
    //std::string cipherKey = "HUVITZ_HUVALLEY_";         // cipherKey
    std::string cipherKey = AES_CIPHER_KEY;
    std::string convertCipherKey = aes128.convertStrToHexStr(cipherKey);        // convert to hex cipherKey
    std::string decryptText = aes128.decryption(str, convertCipherKey);         // decryption
    std::string convertDecryptText = aes128.convertHexStrToStr(decryptText);    // convert to text

    QString rtnStr = QString::fromStdString(convertDecryptText);

    QByteArray ba = QByteArray::fromBase64(rtnStr.toUtf8());

    ui->plainTextEdit_decryption->setPlainText(QString::fromUtf8(ba));
}
