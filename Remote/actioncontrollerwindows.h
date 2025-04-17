#ifndef ACTIONCONTROLLERWINDOWS_H
#define ACTIONCONTROLLERWINDOWS_H

#include "actioncontroller.h"
#include "notifiable.h"

#include <QWidget>

#include "gestures.h"

class ActionControllerWindows : public ActionController
{
    Q_OBJECT
public:
    explicit ActionControllerWindows(Notifiable *output, std::vector<Card::data> *cards);
    virtual ~ActionControllerWindows() override {};

    virtual void play() override;
    virtual void forward() override;
    virtual void backward() override;
    virtual void mute() override;
    virtual void previous() override;
    virtual void next() override;
    virtual void screenshot() override;

    virtual void updateData(std::vector<Card::data> *cards) override;

public slots:
    void actionDispatch(Gesture gesture);
private:
    Notifiable *output;
    std::vector<Card::data> *cards;
};

#endif // ACTIONCONTROLLERWINDOWS_H
