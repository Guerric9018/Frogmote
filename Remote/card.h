#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QWidget>

class Card : public QWidget
{
    Q_OBJECT
public:
    struct data
    {
        int gesture;
        int action;
    };

    explicit Card(QWidget *parent = nullptr, data d = {});

    data getData() const;

private:
    QPixmap backgroundPixmap;
    data data_;

    void paintEvent(QPaintEvent*) override;
signals:
};

#endif // CARD_H
