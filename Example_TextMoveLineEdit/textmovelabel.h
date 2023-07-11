#ifndef TEXTMOVELABEL_H
#define TEXTMOVELABEL_H

#include <QLabel>

class TextMoveWidget;
class TextMoveLabel : public QLabel
{
    Q_OBJECT
private:
    TextMoveWidget *m_textMoveWidget;

public:
    explicit TextMoveLabel(QWidget *parent = nullptr);

    virtual void setText(const QString& text);
};

#endif // TEXTMOVELABEL_H
