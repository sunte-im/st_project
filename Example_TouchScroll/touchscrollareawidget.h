#ifndef TOUCHSCROLLAREAWIDGET_H
#define TOUCHSCROLLAREAWIDGET_H

#include <QScrollArea>

class TouchScrollAreaWidget : public QScrollArea
{
    Q_OBJECT
public:
    enum TYPE
    {
        TYPE_NORMAL_SCROLL,
        TYPE_CENTER_SELECT,
        TYPE_LEFT_RIGHT_SCROLL,
    };

private:
    bool m_mousePressFlag;
    QPoint m_prevPos;
    TYPE m_type;
    int m_upCount;
    int m_downCount;

public:
    explicit TouchScrollAreaWidget(QWidget *parent = nullptr);

    void pressCurrentPos(QEvent* e);
    void moveUpDown(QEvent* e);
    void scrollUp(int moveValue);
    void scrollDown(int moveValue);

    void scrollLeft(int moveValue);
    void scrollRight(int moveValue);

    void setType(TYPE type);
    void setValue(int num);

signals:
    void selectCenterSignals(int value);

protected:
    bool eventFilter(QObject *, QEvent *);

private slots:
    void valueChangedVerticalScrollBar(int value);
};

#endif // TOUCHSCROLLAREAWIDGET_H
