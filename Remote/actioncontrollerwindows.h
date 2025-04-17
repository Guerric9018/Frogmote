#ifndef ACTIONCONTROLLERWINDOWS_H
#define ACTIONCONTROLLERWINDOWS_H

#include "actioncontroller.h"
#include "notifiablewindows.h"

#include <QWidget>

class ActionControllerWindows : public ActionController
{
    Q_OBJECT
public:
    explicit ActionControllerWindows(QWidget *parent);
    virtual ~ActionControllerWindows() override {};

    virtual void play() override;

private:
    NotifiableWindows *notifiable;
};

#endif // ACTIONCONTROLLERWINDOWS_H
