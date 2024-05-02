#include "websocket.h"
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

//! [constructor]
webSocket::webSocket(quint16 port, bool debug, QObject *parent) :
    QObject(parent),
    m_pWebSocketServer(new QWebSocketServer(QStringLiteral("webSocket Server"),
                                            QWebSocketServer::NonSecureMode, this)),
    m_debug(debug)
{
    if (m_pWebSocketServer->listen(QHostAddress::LocalHost, port)) {
        if (m_debug)
            qDebug() << "webSocket listening on port" << port;
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
                this, &webSocket::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &webSocket::closed);
    }
}
//! [constructor]

webSocket::~webSocket()
{
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

//! [onNewConnection]
void webSocket::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &webSocket::processTextMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &webSocket::socketDisconnected);

    m_clients << pSocket;
}
//! [onNewConnection]

//! [processTextMessage]
void webSocket::processTextMessage(QString message)
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "Message received:" << message;
    QStringList parts = message.split(",");
    if ((parts.at(0)== "fatemeh1" && parts.at(1) == "fatemeh1234") ||
        (parts.at(0)== "razieh" && parts.at(1) == "razieh1234") ||
        parts.at(0)== "fatemeh2" && parts.at(1) == "fatemeh1234"){
        if (pClient) {
            pClient->sendTextMessage(parts.at(0));
        }
    }
    else{
        if (pClient) {
            pClient->sendTextMessage("");
        }
    }
}
//! [processTextMessage]


//! [socketDisconnected]
void webSocket::socketDisconnected()
{
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    if (m_debug)
        qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
