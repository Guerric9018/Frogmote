#ifndef URLBAR_H
#define URLBAR_H

#include <QWidget>
#include "urlcheckmark.h"
#include "client.h"
#include "urltextedit.h"

class UrlBar: public QWidget
{
    Q_OBJECT
public:
    UrlBar(QWidget *parent, Notifiable *output, Client *client);
private:
    QPixmap backgroundPixmap;
    UrlCheckMark *urlCheckMark;
    UrlTextEdit *urlTextEdit;
    Client *client;

    void paintEvent(QPaintEvent*) override;
private slots:
    void urlEdited();
};

#endif
