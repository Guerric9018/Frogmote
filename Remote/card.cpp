#include "card.h"

#include <QPainter>

Card::Card(QWidget *parent)
    : QWidget{parent}
{
    backgroundPixmap = QPixmap(":/res/card_frame.png");
    if (backgroundPixmap.isNull()) {
        qWarning("PNG image failed to load");
    }

    float aspectRatio = float(backgroundPixmap.height()) / backgroundPixmap.width();

    int fixedWidth = 300;
    int calculatedHeight = int(fixedWidth * aspectRatio);

    setFixedSize(fixedWidth, calculatedHeight);
}

void Card::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap scaledPixmap = backgroundPixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, scaledPixmap);
    QWidget::paintEvent(event);
}
