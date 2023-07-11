#ifndef CIRCLEMOVEWIDGET_H
#define CIRCLEMOVEWIDGET_H

#include <QWidget>

class QVariantAnimation;
class CircleMoveWidget : public QWidget
{
    Q_OBJECT
    enum STEP
    {
        STEP_1,     // left
        STEP_2,     // right
        STEP_3      // bottom
    };

private:
    QVariantAnimation* m_animation;
    int m_startAngle;
    STEP m_currentStep;

public:
    explicit CircleMoveWidget(QWidget *parent = nullptr);
    ~CircleMoveWidget();

    void moveLeft();
    void moveRight();
    STEP getCurrnetStep();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void valueChangedFromAnimation(const QVariant & value);
    void finishedFromAnimation();
};

#endif // CIRCLEMOVEWIDGET_H
