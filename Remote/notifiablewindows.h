#ifndef NOTIFIABLEWINDOWS_H
#define NOTIFIABLEWINDOWS_H

#include "notifiable.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>

class NotifiableWindows : public Notifiable
{
public:
    explicit NotifiableWindows(QWidget* parent);
    virtual void notify(const QString &file_name, const QString &title, const QString &message) override;
    virtual ~NotifiableWindows() override;
private:
    NOTIFYICONDATA nid;

    HICON static loadHICONFromResource(const QString &file_name, int desired_width = 32, int desired_height = 32);

    QWidget *parent;
};

#endif // NOTIFIABLEWINDOWS_H
