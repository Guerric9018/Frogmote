#ifndef NOTIFIABLE_H
#define NOTIFIABLE_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>

#include <QObject>
#include <QString>

class Notifiable
{
public:
    virtual void notify(const QString &file_name, const QString &title, const QString &message) = 0;
    virtual ~Notifiable() {};
};

#endif // NOTIFIABLE_H
