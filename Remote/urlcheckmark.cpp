#include "urlcheckmark.h"

#include <QPainter>

#include <QDebug>

UrlCheckMark::UrlCheckMark(QWidget *parent): QWidget(parent)
{
    backgroundPixmap = QPixmap(":/res/dots.png");
    setFixedSize(35, 35);
    if (backgroundPixmap.isNull()) {
        qWarning("PNG image failed to load");
    }
}

void UrlCheckMark::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap scaledPixmap = backgroundPixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, scaledPixmap);
    QWidget::paintEvent(event);
}

void UrlCheckMark::updateState(bool validate)
{
    qDebug() << validate;
    if (validate) {
        backgroundPixmap = QPixmap(":/res/url_checkmark.png");
        if (backgroundPixmap.isNull()) {
            qWarning("PNG image failed to load");
        }
        update();
    }
    else {
        backgroundPixmap = QPixmap(":/res/dots.png");
        if (backgroundPixmap.isNull()) {
            qWarning("PNG image failed to load");
        }
        update();
    }
}
