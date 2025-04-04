#include "client.h"
#include <QtWebSockets/QWebSocket>

Client::Client()
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
    qDebug() << "[WebSocket] " << msg;
}
