#include "notifiabledummy.h"
#include <QDebug>

NotifiableDummy::NotifiableDummy(QWidget *parent)
    : parent(parent)
{
}

NotifiableDummy::~NotifiableDummy()
{
}

void NotifiableDummy::notify([[maybe_unused]] const QString &file_name, const QString &title, const QString &message)
{
    qDebug() << "[Dummy] " << title << ": " << message;
}
