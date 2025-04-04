#ifndef URLBAR_H
#define URLBAR_H

#include <QWidget>
#include "urltextedit.h"

class UrlBar: public QWidget
{
    Q_OBJECT
public:
    UrlBar(QWidget *parent);
private:
    QPixmap backgroundPixmap;
    UrlTextEdit *urlTextEdit;
    void paintEvent(QPaintEvent*) override;
};

#endif
