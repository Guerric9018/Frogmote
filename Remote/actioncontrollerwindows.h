#ifndef ACTIONCONTROLLERWINDOWS_H
#define ACTIONCONTROLLERWINDOWS_H

#include "actioncontroller.h"
#include "notifiable.h"

#include <QWidget>

class ActionControllerWindows : public ActionController
{
    Q_OBJECT
public:
    explicit ActionControllerWindows(Notifiable *output);
    virtual ~ActionControllerWindows() override {};

    virtual void play() override;
    virtual void forward() override;
    virtual void backward() override;
    virtual void mute() override;
    virtual void previous() override;
    virtual void next() override;
    virtual void screenshot() override;

private:
    Notifiable *output;
};

#endif // ACTIONCONTROLLERWINDOWS_H
