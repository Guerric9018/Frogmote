#ifndef CLIENT_H
#define CLIENT_H


#include <QWebSocket>

class Client : public QObject
{
public:
    Client();
    ~Client();

private:
    QWebSocket *ws;

    void onConnect();
    void onDisconnect();
    void onMessage(QString msg);
};

#endif // CLIENT_H
