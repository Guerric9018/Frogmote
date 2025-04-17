#ifndef NOTIFIABLE_H
#define NOTIFIABLE_H

#include <QObject>
#include <QString>
#include <QSystemTrayIcon>

class Notifiable
{
public:
    Notifiable(QObject *parent);
    void notify(const QString &file_name, const QString &title, const QString &message);
private:
    QSystemTrayIcon *trayIcon;
};

#endif // NOTIFIABLE_H
