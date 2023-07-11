#ifndef TEXTMOVEWIDGET_H
#define TEXTMOVEWIDGET_H

#include <QGroupBox>

namespace Ui {
class TextMoveWidget;
}

class QTimer;
class TextMoveWidget : public QGroupBox
{
    Q_OBJECT

private:
    Ui::TextMoveWidget *ui;
    QTimer *m_rangeChangedTimer;
    QTimer *m_moveTimer;
    bool m_move;
    bool m_moveRight;
    int m_moveInterval;
    int m_preStepValue;

public:
    explicit TextMoveWidget(QWidget *parent = nullptr);
    ~TextMoveWidget();

    void setText(QString text);
    void setMoveInterval(int msec);

private slots:
    void rangeChanged_fromScrollBar(int min, int max);
    void timeout_fromRangeChangedTimer();
    void timeout_fromMoveTimer();
};

#endif // TEXTMOVEWIDGET_H
