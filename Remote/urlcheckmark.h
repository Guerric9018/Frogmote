#ifndef URLCHECKMARK_H
#define URLCHECKMARK_H

#include <QWidget>

class UrlCheckMark: public QWidget
{
    Q_OBJECT
public:
    UrlCheckMark(QWidget *parent);
    void updateState(bool validate);
private:
    QPixmap backgroundPixmap;
    void paintEvent(QPaintEvent*) override;
};

#endif // URLCHECKMARK_H
