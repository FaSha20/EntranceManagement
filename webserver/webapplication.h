#ifndef WEBAPPLICATION_H
#define WEBAPPLICATION_H

#include <QObject>
#include <QVector>
#include "httpserver.h"
#include "websocket.h"

class WebApplication : public QObject
{
    Q_OBJECT
public:
    explicit WebApplication(QObject *parent = nullptr);
    ~WebApplication();
    bool startServer();
signals:

private:
    HttpServer httpserver;
    quint16 port;
    webSocket socket;
};

#endif // WEBAPPLICATION_H
