#ifndef NOTIFIABLEDUMMY_H
#define NOTIFIABLEDUMMY_H

#include "notifiable.h"

class NotifiableDummy : public Notifiable
{
public:
    explicit NotifiableDummy(QWidget* parent);
    virtual void notify(const QString &file_name, const QString &title, const QString &message) override;
    virtual ~NotifiableDummy() override;

private:
    QWidget *parent;
};

#endif // NOTIFIABLEDUMMY_H
