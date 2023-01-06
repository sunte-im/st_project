#ifndef TIMELINEBEGINENDBODYDIALOG_H
#define TIMELINEBEGINENDBODYDIALOG_H

#include <QDialog>

namespace Ui {
class TimeLineBeginEndBodyDialog;
}

class TimeLineBeginEndBodyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TimeLineBeginEndBodyDialog(QWidget *parent = nullptr);
    ~TimeLineBeginEndBodyDialog();

    void setTimeLinePos(int pos);

    void setMousePressed(bool f);

private:
    Ui::TimeLineBeginEndBodyDialog *ui;
    bool m_mousePressed;
    QPoint m_lastMouseMovePoint;
    int m_timeLinePos;

protected:
    bool nativeEvent(const QByteArray& eventType, void* message, long* result) override;

    void paintEvent(QPaintEvent *);
    bool eventFilter(QObject*, QEvent*);
    void resizeEvent(QResizeEvent*);

signals:
    void moveSignals();
    void moveEndSignals();
};

#endif // TIMELINEBEGINENDBODYDIALOG_H
