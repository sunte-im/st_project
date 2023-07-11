#include "textmovepushbutton.h"
#include "textmovewidget.h"
#include <QVBoxLayout>

TextMovePushButton::TextMovePushButton(QWidget *parent) : QPushButton(parent)
{
    m_textMoveWidget = new TextMoveWidget(this);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_textMoveWidget);
    setLayout(layout);
}

void TextMovePushButton::setText(const QString& text)
{
    m_textMoveWidget->setText(text);
}
