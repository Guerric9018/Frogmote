#ifndef CLIENT_H
#define CLIENT_H

#include "gesturehandler.h"
#include "actioncontroller.h"

#include <QWebSocket>

class Client : public QObject
{
    Q_OBJECT
public:
    Client();
    ~Client();
    void openConnection(const QString &address);
private:
    QWebSocket *ws;
    std::uint64_t epoch;

    GestureHandler *gestureHandler;
    ActionController *actionController;

    void onConnect();
    void onDisconnect();
    void onMessage(QString msg);

signals:
    void connectionStatusChanged(bool connected);
};

#endif // CLIENT_H
