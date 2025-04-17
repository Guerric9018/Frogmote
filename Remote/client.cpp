#include "client.h"
#include <QtWebSockets/QWebSocket>
#include <QJsonObject>
#include <QJsonArray>

Client::Client()
    : ws(nullptr)
    , epoch(0)
{
    gestureHandler = new GestureHandler(this);
    connect(gestureHandler, &GestureHandler::gestureDetected, this, [](int code) { qDebug() << "Code: " << code; });
    qDebug() << "[WebSocket] Created";
}

Client::~Client()
{
    if (ws) {
        ws->close();
        ws->deleteLater();
    }
}

void Client::openConnection(const QString &address)
{
    if (ws) {
        ws->close();
        ws->deleteLater();
        ws = nullptr;
    }

    QUrl url(address + "/sensor/connect?type=android.sensor.orientation");
    ws = new QWebSocket();
    connect(ws, &QWebSocket::connected, this, &Client::onConnect);
    connect(ws, &QWebSocket::disconnected, this, &Client::onDisconnect);
    ws->open(url);
    qDebug() << "[WebSocket] Attempting connection to" << url.toString();
}

void Client::onConnect()
{
    qDebug() << "[WebSocket] Connected";
    connect(ws, &QWebSocket::textMessageReceived, this, &Client::onMessage);
    emit connectionStatusChanged(true);
}

void Client::onDisconnect()
{
    qDebug() << "[WebSocket] Disconnected" << ws->closeReason();
    emit connectionStatusChanged(false);
}

void Client::onMessage(QString msg)
{
    const auto json = QJsonDocument::fromJson(QByteArray(msg.toStdString().c_str())).object();
    enum {
        sent_values,
        sent_timestamp,
        num_sent
    };
    int sent_mask = 0, expected_mask = (1 << num_sent) - 1;

    gestureHandler->processData(json);

    if (const auto v = json["values"]; v.isArray()) {
        if (const auto values = v.toArray(); values.size() == 3) {
            for (qsizetype i = 0; i < 3; ++i) {
            }
            sent_mask |= 1 << sent_values;
        }
    }

    if (const auto v = json["timestamp"]; v.isDouble()) {
        const auto value = v.toInteger();
        if (!epoch) {
            epoch = value;
        }
        sent_mask |= 1 << sent_timestamp;
    }

    if (sent_mask != expected_mask) {
        qDebug() << "[WebSocket] incomplete message: " << msg;
    }
}
