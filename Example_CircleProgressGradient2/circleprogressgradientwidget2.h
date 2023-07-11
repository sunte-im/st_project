#ifndef CIRCLEPROGRESSGRADIENTWIDGET2_H
#define CIRCLEPROGRESSGRADIENTWIDGET2_H

#include <QWidget>

class CircleProgressGradientWidget2 : public QWidget
{
    Q_OBJECT
private:
    qreal m_value;
    QString m_colorStart;
    QString m_colorEnd;
    QString m_colorHeadCircle;
    bool m_visible;

public:
    explicit CircleProgressGradientWidget2(QWidget *parent = nullptr);

    void _setVisible(bool f);
    void setValue(int value);       // 1~100
    void setProgressGradientColor(QString start, QString end, QString headCircle);      // ex) #00e1d2, #00a2fa, #079df3

protected:
     void paintEvent(QPaintEvent *);

};

#endif // CIRCLEPROGRESSGRADIENTWIDGET2_H
