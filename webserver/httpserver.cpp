#include "httpserver.h"

HttpServer::HttpServer(QObject *parent) : QObject(parent), m_httpPort(8080), m_sslPort(8082)
{
}


bool HttpServer::startServer()
{
    if (!setupRoutes()) {
        qWarning() << "Failed to setup routes.";
        return false;
    }

    if (!m_httpServer.listen(QHostAddress::LocalHost, m_httpPort)) {
        qWarning() << "Failed to listen on HTTP port.";
        return false;
    }

    // if (!setupSSL()) {
    //     qWarning() << "Failed to setup SSL.";
    //     return false;
    // }
    setupSSL();
    qInfo().noquote() << QString("Running on http://127.0.0.1:%1/ and https://127.0.0.1:%2/ (Press CTRL+C to quit)").arg(m_httpPort).arg(m_sslPort);
    return true;
}


bool HttpServer::setupRoutes()
{
    m_httpServer.route("/auth", [this](const QHttpServerRequest &request) {
        auto auth = request.value("authorization");

        if (auth == "810199440" || auth == "810199443" || auth == "810199419") {
            // User newUser("newUserId", QDate::currentDate(), QTime::currentTime());
            users.append(auth + QDate::currentDate().toString()+QTime::currentTime().toString());
            return QHttpServerResponse("text/plain", "Success\n", QHttpServerResponse::StatusCode::Ok);
        }
        QHttpServerResponse response("text/plain", "invalid\n",
                                     QHttpServerResponse::StatusCode::Unauthorized);
        response.setHeader("WWW-Authenticate", R"(Basic realm="Simple example", charset="UTF-8")");
        return response;
    });

    return true;
}

bool HttpServer::setupSSL()
{

    #if QT_CONFIG(ssl)
        const auto sslCertificateChain =
            QSslCertificate::fromPath(QStringLiteral("C:/Qt/Examples/Qt-6.7.0/httpserver/simple/assets/certificate.crt"));
        if (sslCertificateChain.empty()) {
            qWarning() << "Couldn't retrieve SSL certificate from file.";
            return false;
        }

        QFile privateKeyFile(QStringLiteral("C:/Qt/Examples/Qt-6.7.0/httpserver/simple/assets/private.key"));
        if (!privateKeyFile.open(QIODevice::ReadOnly)) {
            qWarning() << QCoreApplication::translate("QHttpServerExample",
                                                      "Couldn't open file for reading: %1")
                              .arg(privateKeyFile.errorString());
            return false;
        }

        m_httpServer.sslSetup(sslCertificateChain.front(), QSslKey(&privateKeyFile, QSsl::Rsa));
        privateKeyFile.close();

        const auto sslPort = m_httpServer.listen(QHostAddress::LocalHost,m_sslPort);
        if (!sslPort) {
            qWarning() << QCoreApplication::translate("QHttpServerExample",
                                                      "Server failed to listen on a port.");
            return false;
        }
    #else
        qInfo().noquote()
            << QCoreApplication::translate("QHttpServerExample",
                                           "Running on http://127.0.0.1:%1/"
                                           "(Press CTRL+C to quit)").arg(m_httpPort);
    #endif

    return true;
}
