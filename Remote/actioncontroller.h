#ifndef ACTIONCONTROLLER_H
#define ACTIONCONTROLLER_H

#include "gesturehandler.h"

#include <QObject>

class ActionController : public QObject
{
    Q_OBJECT
public:
    virtual void play() = 0;
    virtual void forward() = 0;
    virtual void backward() = 0;
    virtual void mute() = 0;
    virtual ~ActionController() {};
public slots:
    void actionDispatch(GestureHandler::Code code);
};

#endif // ACTIONCONTROLLER_H
