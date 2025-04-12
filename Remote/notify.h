#ifndef NOTIFY_H
#define NOTIFY_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>

#include <QObject>
#include <QString>

class Notify : public QObject
{
    Q_OBJECT
public:
    Notify(QObject* parent, const QString &file_name, const QString &title, const QString &message, HWND hwnd);
private:
    NOTIFYICONDATA nid;

    HICON static loadHICONFromResource(const QString &file_name, int desired_width = 32, int desired_height = 32);
};

#endif // NOTIFY_H
