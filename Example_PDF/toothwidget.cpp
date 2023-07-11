#include "toothwidget.h"
#include "ui_toothwidget.h"
//#include "configuration.h"
//#include "func.h"
#include <QDebug>

ToothWidget::ToothWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToothWidget)
{
    ui->setupUi(this);

    init();
}

ToothWidget::~ToothWidget()
{
    delete ui;
}

void ToothWidget::init()
{
    m_toothLabelList << ui->label_11
                     << ui->label_12
                     << ui->label_13
                     << ui->label_14
                     << ui->label_15
                     << ui->label_16
                     << ui->label_17
                     << ui->label_18
                     << ui->label_21
                     << ui->label_22
                     << ui->label_23
                     << ui->label_24
                     << ui->label_25
                     << ui->label_26
                     << ui->label_27
                     << ui->label_28
                     << ui->label_31
                     << ui->label_32
                     << ui->label_33
                     << ui->label_34
                     << ui->label_35
                     << ui->label_36
                     << ui->label_37
                     << ui->label_38
                     << ui->label_41
                     << ui->label_42
                     << ui->label_43
                     << ui->label_44
                     << ui->label_45
                     << ui->label_46
                     << ui->label_47
                     << ui->label_48;

    ui->label_11->setProperty("number", "11");
    ui->label_12->setProperty("number", "12");
    ui->label_13->setProperty("number", "13");
    ui->label_14->setProperty("number", "14");
    ui->label_15->setProperty("number", "15");
    ui->label_16->setProperty("number", "16");
    ui->label_17->setProperty("number", "17");
    ui->label_18->setProperty("number", "18");
    ui->label_21->setProperty("number", "21");
    ui->label_22->setProperty("number", "22");
    ui->label_23->setProperty("number", "23");
    ui->label_24->setProperty("number", "24");
    ui->label_25->setProperty("number", "25");
    ui->label_26->setProperty("number", "26");
    ui->label_27->setProperty("number", "27");
    ui->label_28->setProperty("number", "28");
    ui->label_31->setProperty("number", "31");
    ui->label_32->setProperty("number", "32");
    ui->label_33->setProperty("number", "33");
    ui->label_34->setProperty("number", "34");
    ui->label_35->setProperty("number", "35");
    ui->label_36->setProperty("number", "36");
    ui->label_37->setProperty("number", "37");
    ui->label_38->setProperty("number", "38");
    ui->label_41->setProperty("number", "41");
    ui->label_42->setProperty("number", "42");
    ui->label_43->setProperty("number", "43");
    ui->label_44->setProperty("number", "44");
    ui->label_45->setProperty("number", "45");
    ui->label_46->setProperty("number", "46");
    ui->label_47->setProperty("number", "47");
    ui->label_48->setProperty("number", "48");

    m_numLabelList << ui->label__11
                   << ui->label__12
                   << ui->label__13
                   << ui->label__14
                   << ui->label__15
                   << ui->label__16
                   << ui->label__17
                   << ui->label__18
                   << ui->label__21
                   << ui->label__22
                   << ui->label__23
                   << ui->label__24
                   << ui->label__25
                   << ui->label__26
                   << ui->label__27
                   << ui->label__28
                   << ui->label__31
                   << ui->label__32
                   << ui->label__33
                   << ui->label__34
                   << ui->label__35
                   << ui->label__36
                   << ui->label__37
                   << ui->label__38
                   << ui->label__41
                   << ui->label__42
                   << ui->label__43
                   << ui->label__44
                   << ui->label__45
                   << ui->label__46
                   << ui->label__47
                   << ui->label__48;

    ui->label__11->setProperty("number", "11");
    ui->label__12->setProperty("number", "12");
    ui->label__13->setProperty("number", "13");
    ui->label__14->setProperty("number", "14");
    ui->label__15->setProperty("number", "15");
    ui->label__16->setProperty("number", "16");
    ui->label__17->setProperty("number", "17");
    ui->label__18->setProperty("number", "18");
    ui->label__21->setProperty("number", "21");
    ui->label__22->setProperty("number", "22");
    ui->label__23->setProperty("number", "23");
    ui->label__24->setProperty("number", "24");
    ui->label__25->setProperty("number", "25");
    ui->label__26->setProperty("number", "26");
    ui->label__27->setProperty("number", "27");
    ui->label__28->setProperty("number", "28");
    ui->label__31->setProperty("number", "31");
    ui->label__32->setProperty("number", "32");
    ui->label__33->setProperty("number", "33");
    ui->label__34->setProperty("number", "34");
    ui->label__35->setProperty("number", "35");
    ui->label__36->setProperty("number", "36");
    ui->label__37->setProperty("number", "37");
    ui->label__38->setProperty("number", "38");
    ui->label__41->setProperty("number", "41");
    ui->label__42->setProperty("number", "42");
    ui->label__43->setProperty("number", "43");
    ui->label__44->setProperty("number", "44");
    ui->label__45->setProperty("number", "45");
    ui->label__46->setProperty("number", "46");
    ui->label__47->setProperty("number", "47");
    ui->label__48->setProperty("number", "48");

    m_btnList << ui->pushButton_32
              << ui->pushButton_29
              << ui->pushButton_28
              << ui->pushButton_27
              << ui->pushButton_22
              << ui->pushButton_23
              << ui->pushButton_18
              << ui->pushButton_30
              << ui->pushButton_25
              << ui->pushButton_20
              << ui->pushButton_24
              << ui->pushButton_31
              << ui->pushButton_17
              << ui->pushButton_26
              << ui->pushButton
              << ui->pushButton_2
              << ui->pushButton_21
              << ui->pushButton_15
              << ui->pushButton_14
              << ui->pushButton_11
              << ui->pushButton_9
              << ui->pushButton_5
              << ui->pushButton_4
              << ui->pushButton_3
              << ui->pushButton_19
              << ui->pushButton_16
              << ui->pushButton_13
              << ui->pushButton_12
              << ui->pushButton_10
              << ui->pushButton_8
              << ui->pushButton_7
              << ui->pushButton_6;

    foreach (QPushButton* btn, m_btnList)
    {
        connect(btn, SIGNAL(clicked()), this, SLOT(clickedButton()));
    }

    // image > top left
    ui->pushButton_32->setProperty("number", "11");
    ui->pushButton_29->setProperty("number", "12");
    ui->pushButton_28->setProperty("number", "13");
    ui->pushButton_27->setProperty("number", "14");
    ui->pushButton_22->setProperty("number", "15");
    ui->pushButton_23->setProperty("number", "16");
    ui->pushButton_18->setProperty("number", "17");
    ui->pushButton_30->setProperty("number", "18");

    // image > top right
    ui->pushButton_25->setProperty("number", "21");
    ui->pushButton_20->setProperty("number", "22");
    ui->pushButton_24->setProperty("number", "23");
    ui->pushButton_31->setProperty("number", "24");
    ui->pushButton_17->setProperty("number", "25");
    ui->pushButton_26->setProperty("number", "26");
    ui->pushButton->setProperty("number", "27");
    ui->pushButton_2->setProperty("number", "28");

    // image > bottom left
    ui->pushButton_21->setProperty("number", "41");
    ui->pushButton_15->setProperty("number", "42");
    ui->pushButton_14->setProperty("number", "43");
    ui->pushButton_11->setProperty("number", "44");
    ui->pushButton_9->setProperty("number", "45");
    ui->pushButton_5->setProperty("number", "46");
    ui->pushButton_4->setProperty("number", "47");
    ui->pushButton_3->setProperty("number", "48");

    // image > bottom right
    ui->pushButton_19->setProperty("number", "31");
    ui->pushButton_16->setProperty("number", "32");
    ui->pushButton_13->setProperty("number", "33");
    ui->pushButton_12->setProperty("number", "34");
    ui->pushButton_10->setProperty("number", "35");
    ui->pushButton_8->setProperty("number", "36");
    ui->pushButton_7->setProperty("number", "37");
    ui->pushButton_6->setProperty("number", "38");

    // FDI, US
    //updateUi_teethLabeling();
}

void ToothWidget::setClickedEnable(bool f)
{
    foreach (QPushButton* btn, m_btnList)
    {
        btn->setEnabled(f);
    }
}

void ToothWidget::setType(QString num, QString item)
{
    // tooth image
    foreach (QLabel* label, m_toothLabelList)
    {
        QString labelNum = label->property("number").toString();
        if (labelNum != num)
            continue;

        label->setProperty("type", item);
        break;
    }

    // number
    foreach (QLabel* label, m_numLabelList)
    {
        QString labelNum = label->property("number").toString();
        if (labelNum != num)
            continue;

        label->setProperty("type", item);
        break;
    }
}

void ToothWidget::select(QString num)
{
    // tooth image
    foreach (QLabel* label, m_toothLabelList)
    {
        QString labelNum = label->property("number").toString();
        if (labelNum != num)
            continue;

        label->setStyleSheet("QLabel{border-image: url(:/images/img_tooth_select_"+labelNum+".png);}");
        break;
    }

    // number
    foreach (QLabel* label, m_numLabelList)
    {
        QString labelNum = label->property("number").toString();
        if (labelNum != num)
            continue;

        label->setStyleSheet("QLabel{font-family: Roboto; font-weight: bold; font-size: 14px; color:#6a6c6e;}");
        break;
    }
}

void ToothWidget::updateUi()
{
    // tooth image
    foreach (QLabel* label, m_toothLabelList)
    {
        QString num = label->property("number").toString();
        QString type= label->property("type").toString();

        if (type.isEmpty())
            label->setStyleSheet("");
        else
            label->setStyleSheet("QLabel{border-image: url(:/images/img_tooth_"+type.toLower()+"_"+num+".png);}");
    }

    // number
    foreach (QLabel* label, m_numLabelList)
    {
        QString type= label->property("type").toString();
        QString textColor = "#c7c8cb";
        if (type == "Inlay")         textColor = "#F7A189";
        else if (type == "Onlay")    textColor = "#F78A8D";
        else if (type == "Crown")    textColor = "#68AAFB";
        else if (type == "Veneer")   textColor = "#AD99EE";

        label->setStyleSheet("QLabel{font-family: Roboto; font-weight: bold; font-size: 14px; color:"+textColor+";}");
    }
}

/*
void ToothWidget::updateUi_teethLabeling()
{
    QString teethLabelingType = Configuration::getInstance()->teethLabeling();
    if (teethLabelingType == "FDI")
    {
        ui->label__11->setText("11");
        ui->label__12->setText("12");
        ui->label__13->setText("13");
        ui->label__14->setText("14");
        ui->label__15->setText("15");
        ui->label__16->setText("16");
        ui->label__17->setText("17");
        ui->label__18->setText("18");
        ui->label__21->setText("21");
        ui->label__22->setText("22");
        ui->label__23->setText("23");
        ui->label__24->setText("24");
        ui->label__25->setText("25");
        ui->label__26->setText("26");
        ui->label__27->setText("27");
        ui->label__28->setText("28");
        ui->label__31->setText("31");
        ui->label__32->setText("32");
        ui->label__33->setText("33");
        ui->label__34->setText("34");
        ui->label__35->setText("35");
        ui->label__36->setText("36");
        ui->label__37->setText("37");
        ui->label__38->setText("38");
        ui->label__41->setText("41");
        ui->label__42->setText("42");
        ui->label__43->setText("43");
        ui->label__44->setText("44");
        ui->label__45->setText("45");
        ui->label__46->setText("46");
        ui->label__47->setText("47");
        ui->label__48->setText("48");
    }
    if (teethLabelingType == "US")
    {
        ui->label__11->setText(func::teethLabelingToChange_us("11"));
        ui->label__12->setText(func::teethLabelingToChange_us("12"));
        ui->label__13->setText(func::teethLabelingToChange_us("13"));
        ui->label__14->setText(func::teethLabelingToChange_us("14"));
        ui->label__15->setText(func::teethLabelingToChange_us("15"));
        ui->label__16->setText(func::teethLabelingToChange_us("16"));
        ui->label__17->setText(func::teethLabelingToChange_us("17"));
        ui->label__18->setText(func::teethLabelingToChange_us("18"));
        ui->label__21->setText(func::teethLabelingToChange_us("21"));
        ui->label__22->setText(func::teethLabelingToChange_us("22"));
        ui->label__23->setText(func::teethLabelingToChange_us("23"));
        ui->label__24->setText(func::teethLabelingToChange_us("24"));
        ui->label__25->setText(func::teethLabelingToChange_us("25"));
        ui->label__26->setText(func::teethLabelingToChange_us("26"));
        ui->label__27->setText(func::teethLabelingToChange_us("27"));
        ui->label__28->setText(func::teethLabelingToChange_us("28"));
        ui->label__31->setText(func::teethLabelingToChange_us("31"));
        ui->label__32->setText(func::teethLabelingToChange_us("32"));
        ui->label__33->setText(func::teethLabelingToChange_us("33"));
        ui->label__34->setText(func::teethLabelingToChange_us("34"));
        ui->label__35->setText(func::teethLabelingToChange_us("35"));
        ui->label__36->setText(func::teethLabelingToChange_us("36"));
        ui->label__37->setText(func::teethLabelingToChange_us("37"));
        ui->label__38->setText(func::teethLabelingToChange_us("38"));
        ui->label__41->setText(func::teethLabelingToChange_us("41"));
        ui->label__42->setText(func::teethLabelingToChange_us("42"));
        ui->label__43->setText(func::teethLabelingToChange_us("43"));
        ui->label__44->setText(func::teethLabelingToChange_us("44"));
        ui->label__45->setText(func::teethLabelingToChange_us("45"));
        ui->label__46->setText(func::teethLabelingToChange_us("46"));
        ui->label__47->setText(func::teethLabelingToChange_us("47"));
        ui->label__48->setText(func::teethLabelingToChange_us("48"));
    }
}
*/
void ToothWidget::clear()
{
    // tooth image
    foreach (QLabel* label, m_toothLabelList)
        label->setProperty("type", "");

    // number
    foreach (QLabel* label, m_numLabelList)
        label->setProperty("type", "");

    updateUi();
}

void ToothWidget::clickedButton()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    QString btnNum = btn->property("number").toString();

    qDebug() << "ToothWidget::clickedButton num: " << btnNum;
    
    emit clicked(btnNum);

    updateUi();

    select(btnNum);
}
