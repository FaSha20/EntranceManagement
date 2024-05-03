#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QObject>
#include <QtCore/QList>
#include <QVector>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class webSocket : public QObject
{
    Q_OBJECT
public:
    explicit webSocket(quint16 port, bool debug = false, QObject *parent = nullptr);
    ~webSocket();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onNewConnection();
    void processTextMessage(QString message);
    void socketDisconnected();

private:
    QWebSocketServer *m_pWebSocketServer;
    QList<QWebSocket *> m_clients;
    bool m_debug;
    QVector<QString> users;
};

#endif // WEBSOCKET_H
