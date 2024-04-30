#include "httpserver.h"

HttpServer::HttpServer(QObject *parent) : QObject(parent)
{
    connect(&m_httpServer, &QHttpServer::newRequest, this, &HttpServer::handleHttpRequests);

    // Start listening on port 8080
    const auto port = m_httpServer.listen(QHostAddress::LocalHost, 8080);
    if (!port) {
        qWarning() << QCoreApplication::translate("HttpServer",
                                                  "Server failed to listen on a port.");
    }
}

void HttpServer::handleHttpRequests()
{
    auto request = m_httpServer.nextRequest();
    if (!request)
        return;

    auto response = handleRoute(request->path(), *request);
    m_httpServer.send(std::move(*request), std::move(response));
}

QHttpServerResponse HttpServer::handleRoute(const QString &path, const QHttpServerRequest &request)
{
    // Your route handling logic goes here
    // Modify the logic based on your requirements
    if (path == "/") {
        return QHttpServerResponse("text/plain", "Hello world");
    } else if (path == "/query") {
        return QHttpServerResponse("text/plain", host(request) + "/query/");
    } else {
        // Handle other routes
        // You can use request parameters to further process the request
        return QHttpServerResponse("text/plain", "Unknown route");
    }
}

QString HttpServer::host(const QHttpServerRequest &request)
{
    return QString::fromLatin1(request.value("Host"));
}
