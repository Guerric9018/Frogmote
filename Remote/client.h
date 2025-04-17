#ifndef CLIENT_H
#define CLIENT_H

#include "gesturehandler.h"
#include "actioncontroller.h"
#include "notifiable.h"

#include <QWebSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    Client(Notifiable *output);
    ~Client();
    void openConnection(const QString &address);
private:
    QWebSocket *ws;
    std::uint64_t epoch;

    GestureHandler *gestureHandler;
    ActionController *actionController;
    Notifiable *output;

    void onConnect();
    void onDisconnect();
    void onMessage(QString msg);

signals:
    void connectionStatusChanged(bool connected);
};

#endif // CLIENT_H
