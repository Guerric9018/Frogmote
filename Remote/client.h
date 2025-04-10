#ifndef CLIENT_H
#define CLIENT_H


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

    void onConnect();
    void onDisconnect();
    void onMessage(QString msg);

signals:
    void connectionStatusChanged(bool connected);
};

#endif // CLIENT_H
