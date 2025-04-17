#include "notifiable.h"

Notifiable::Notifiable(QObject *parent)
{
    trayIcon = new QSystemTrayIcon(parent);
    trayIcon->setIcon(QIcon(":/res/logo.png"));
    trayIcon->show();
}

void Notifiable::notify([[maybe_unused]] const QString &file_name, const QString &title, const QString &message) const
{
    trayIcon->showMessage(title, message, QSystemTrayIcon::Information, 2500);
}
