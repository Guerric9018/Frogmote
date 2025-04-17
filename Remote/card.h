#ifndef CARD_H
#define CARD_H

#include <QObject>
#include <QWidget>

#include "gestures.h"
#include "actions.h"

class Card : public QWidget
{
    Q_OBJECT
public:
    struct data
    {
        Gesture gesture;
        Action action;
    };

    explicit Card(QWidget *parent = nullptr, data *d = nullptr);

    data getData() const;

private:
    QPixmap backgroundPixmap;
    data *data_;

    QWidget gestureImage;
    QWidget actionImage;

    void paintEvent(QPaintEvent*) override;
private slots:
    void gestureChanged(int gesture);
    void actionChanged(int action);
};

#endif // CARD_H
