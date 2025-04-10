#ifndef URLBAR_H
#define URLBAR_H

#include <QWidget>
#include "urlcheckmark.h"
#include "client.h"

class UrlBar: public QWidget
{
    Q_OBJECT
public:
    UrlBar(QWidget *parent);
private:
    QPixmap backgroundPixmap;
    UrlCheckMark *urlCheckMark;
    Client *client;

    void paintEvent(QPaintEvent*) override;
private slots:
    void urlEdited(const QString &newText);
};

#endif
