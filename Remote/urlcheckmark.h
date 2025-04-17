#ifndef URLCHECKMARK_H
#define URLCHECKMARK_H

#include <QWidget>
#include "notifiable.h"

class UrlCheckMark: public QWidget
{
    Q_OBJECT
public:
    UrlCheckMark(QWidget *parent, Notifiable *output);
    void updateState(bool validate);
private:
    QPixmap backgroundPixmap;
    void paintEvent(QPaintEvent*) override;
    std::unique_ptr<Notifiable> output;
};

#endif // URLCHECKMARK_H
