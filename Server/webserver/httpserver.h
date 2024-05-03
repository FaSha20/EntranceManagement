#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QObject>
#include <QHttpServer>
#include <QCoreApplication>
#include <QFile>
#include <QSslCertificate>
#include <QSslKey>
// #include "user.h"

class HttpServer : public QObject
{
    Q_OBJECT
public:
    explicit HttpServer(QObject *parent = nullptr);

    bool startServer();

private:
    QHttpServer m_httpServer;
    quint16 m_httpPort;
    quint16 m_sslPort;



    bool setupRoutes();
    bool setupSSL();
};

#endif // HTTPSERVER_H
