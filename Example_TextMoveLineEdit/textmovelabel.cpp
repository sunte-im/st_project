#include "textmovelabel.h"
#include "textmovewidget.h"
#include <QVBoxLayout>

TextMoveLabel::TextMoveLabel(QWidget *parent) : QLabel(parent)
{
    m_textMoveWidget = new TextMoveWidget(this);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(m_textMoveWidget);
    setLayout(layout);
}

void TextMoveLabel::setText(const QString& text)
{
    m_textMoveWidget->setText(text);
}
