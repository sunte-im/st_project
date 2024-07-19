#ifndef CIRCLEBAR_H
#define CIRCLEBAR_H

#include <QWidget>

class CircleBar : public QWidget
{
    Q_OBJECT

public:
    struct st_circlebar_item
    {
        qreal p=0;
        QString color="ffffff";

        st_circlebar_item(qreal p_, QString color_) { p = p_; color = color_;}
    };

private:
    qreal m_p; // progress 0.0 to 1.0
    QList<st_circlebar_item> m_itemList;

public:
    explicit CircleBar(QWidget *parent = nullptr);

    void update_(qreal pp);

    void addItem(int p, QString color);

protected:
    void paintEvent(QPaintEvent *);

signals:

};

#endif // CIRCLEBAR_H
