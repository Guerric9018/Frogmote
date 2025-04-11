#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QWidget>

class Card : public QWidget
{
    Q_OBJECT
public:
    explicit Card(QWidget *parent = nullptr);
private:
    QPixmap backgroundPixmap;

    void paintEvent(QPaintEvent*) override;
signals:
};

#endif // CARD_H
