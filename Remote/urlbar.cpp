#include "urlbar.h"

#include <QPainter>
#include <QHBoxLayout>
#include <QLabel>
#include "urltextedit.h"

UrlBar::UrlBar(QWidget *parent): QWidget(parent) {
    setFixedSize(500, 50);

    QHBoxLayout *layout = new QHBoxLayout;
    this->setLayout(layout);
    layout->setSpacing(10);

    urlCheckMark = new UrlCheckMark(this);
    layout->addWidget(urlCheckMark);

    urlTextEdit = new UrlTextEdit(this);
    urlTextEdit->setPlaceholderText("111.111.111.111:8000");
    layout->addWidget(urlTextEdit);

    connect(urlTextEdit, &QLineEdit::editingFinished,
            this, &UrlBar::urlEdited);

    client = new Client();
    connect(client, &Client::connectionStatusChanged,
            urlCheckMark, &UrlCheckMark::updateState);

    backgroundPixmap = QPixmap(":/res/url_text_edit.png");
    if (backgroundPixmap.isNull()) {
        qWarning("PNG image failed to load");
    }
}

void UrlBar::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap scaledPixmap = backgroundPixmap.scaled(size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, scaledPixmap);
    QWidget::paintEvent(event);
}

void UrlBar::urlEdited()
{
    client->openConnection(urlTextEdit->text());
}
