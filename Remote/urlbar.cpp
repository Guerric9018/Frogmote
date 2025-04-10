#include "urlbar.h"

#include <QPainter>
#include <QHBoxLayout>
#include "urltextedit.h"

UrlBar::UrlBar(QWidget *parent): QWidget(parent) {
    setFixedSize(500, 50);

    QHBoxLayout *layout = new QHBoxLayout;
    this->setLayout(layout);

    urlCheckMark = new UrlCheckMark(this);
    layout->addWidget(urlCheckMark);

    UrlTextEdit *urlTextEdit = new UrlTextEdit(this);
    layout->addWidget(urlTextEdit);

    connect(urlTextEdit, &QLineEdit::textChanged,
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

void UrlBar::urlEdited(const QString &newText)
{
    client->openConnection(newText);
}
