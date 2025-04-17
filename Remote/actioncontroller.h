#ifndef ACTIONCONTROLLER_H
#define ACTIONCONTROLLER_H

#include <QObject>
#include "card.h"

class ActionController : public QObject
{
    Q_OBJECT
public:
    virtual void play() = 0;
    virtual void forward() = 0;
    virtual void backward() = 0;
    virtual void mute() = 0;
    virtual void previous() = 0;
    virtual void next() = 0;
    virtual void screenshot() = 0;

    virtual void updateData(std::vector<Card::data> *cards) = 0;

    virtual ~ActionController() {};
};

#endif // ACTIONCONTROLLER_H
