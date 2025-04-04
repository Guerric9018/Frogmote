#include "client.h"
#include <QtWebSockets/QWebSocket>
#include <QJsonObject>
#include <QJsonArray>

Client::Client()
    : epoch(0)
{
    auto url = QString("ws://137.194.156.142:8081/sensor/connect?type=android.sensor.orientation");
    ws = new QWebSocket(url);
    connect(ws, &QWebSocket::connected, this, &Client::onConnect);
    connect(ws, &QWebSocket::disconnected, this, &Client::onDisconnect);
    ws->open(url);
    qDebug() << "[WebSocket] Initialized";
}

Client::~Client()
{
    delete ws;
}

void Client::onConnect()
{
    qDebug() << "[WebSocket] Connected";
    connect(ws, &QWebSocket::textMessageReceived, this, &Client::onMessage);
}

void Client::onDisconnect()
{
    qDebug() << "[WebSocket] Disconnected" << ws->closeReason();
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
    auto out = qDebug().nospace();

    if (const auto v = json["values"]; v.isArray()) {
        if (const auto values = v.toArray(); values.size() == 3) {
            out << "[WebSocket.values] ";
            for (qsizetype i = 0; i < 3; ++i) {
                out << "xyz"[i] << '=' << values[i].toDouble(std::nan("")) << ',' << ' ';
            }
            sent_mask |= 1 << sent_values;
        }
    }

    if (const auto v = json["timestamp"]; v.isDouble()) {
        const auto value = v.toInteger();
        if (!epoch) {
            epoch = value;
        }
        out << "[WebSocket.timestamp] " << float(value - epoch) / 1e6 << "ms";
        sent_mask |= 1 << sent_timestamp;
    }

    if (sent_mask != expected_mask) {
        qDebug() << "[WebSocket] incomplete message: " << msg;
    }
}
