#ifndef CIRCLEPROGRESSGRADIENTWIDGET_H
#define CIRCLEPROGRESSGRADIENTWIDGET_H

#include <QWidget>
class CircleProgressGradientWidget : public QWidget
{
    Q_OBJECT
private:
    qreal m_value;
    QString m_colorStart;
    QString m_colorEnd;
    QString m_colorHeadCircle;

public:
    explicit CircleProgressGradientWidget(QWidget *parent = nullptr);
    ~CircleProgressGradientWidget();

    void setValue(int value);       // 1~100
    void setProgressGradientColor(QString start, QString end, QString headCircle);      // ex) #00e1d2, #00a2fa, #079df3

protected:
     void paintEvent(QPaintEvent *);

};

#endif // CIRCLEPROGRESSGRADIENTWIDGET_H
