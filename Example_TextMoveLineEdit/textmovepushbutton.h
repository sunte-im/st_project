#ifndef TEXTMOVEPUSHBUTTON_H
#define TEXTMOVEPUSHBUTTON_H

#include <QPushButton>

class TextMoveWidget;
class TextMovePushButton : public QPushButton
{
    Q_OBJECT
private:
    TextMoveWidget *m_textMoveWidget;

public:
    explicit TextMovePushButton(QWidget *parent = nullptr);

    virtual void setText(const QString& text);

};

#endif // TEXTMOVEPUSHBUTTON_H
