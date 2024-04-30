
#include <QHttpServer>
#include <QHttpServerResponse>

#if QT_CONFIG(ssl)
// # include <QS
#  include <QSslCertificate>
#  include <QtNetwork/QSslKey>
#endif

#include <QCoreApplication>
#include <QFile>
#include <QJsonObject>
#include <QString>

    using namespace Qt::StringLiterals;

static inline QString host(const QHttpServerRequest &request)
{
    return QString::fromLatin1(request.value("Host"));
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    QHttpServer httpServer;
    httpServer.route("/auth", [](const QHttpServerRequest &request) {
        auto auth = request.value("authorization");

        if (auth == "810199440") {
            return QHttpServerResponse("text/plain", "Success\n", QHttpServerResponse::StatusCode::Ok);
        }
        QHttpServerResponse response("text/plain", "invalid\n",
                                     QHttpServerResponse::StatusCode::Unauthorized);
        response.setHeader("WWW-Authenticate", R"(Basic realm="Simple example", charset="UTF-8")");
        return response;
    });

    httpServer.afterRequest([](QHttpServerResponse &&resp) {
        resp.setHeader("Server", "Qt HTTP Server");
        return std::move(resp);
    });

    const auto port = httpServer.listen(QHostAddress::LocalHost,8080);
    if (!port) {
        qWarning() << QCoreApplication::translate("QHttpServerExample",
                                                  "Server failed to listen on a port.");
        return -1;
    }

#if QT_CONFIG(ssl)
    const auto sslCertificateChain =
        QSslCertificate::fromPath(QStringLiteral("C:/Qt/Examples/Qt-6.7.0/httpserver/simple/assets/certificate.crt"));
    if (sslCertificateChain.empty()) {
        qWarning() << QCoreApplication::translate("QHttpServerExample",
                                                  "Couldn't retrieve SSL certificate from file.");
        return -1;
    }
    QFile privateKeyFile(QStringLiteral("C:/Qt/Examples/Qt-6.7.0/httpserver/simple/assets/private.key"));
    if (!privateKeyFile.open(QIODevice::ReadOnly)) {
        qWarning() << QCoreApplication::translate("QHttpServerExample",
                                                  "Couldn't open file for reading: %1")
                          .arg(privateKeyFile.errorString());
        return -1;
    }
    httpServer.sslSetup(sslCertificateChain.front(), QSslKey(&privateKeyFile, QSsl::Rsa));
    privateKeyFile.close();

    const auto sslPort = httpServer.listen(QHostAddress::LocalHost,8082);
    if (!sslPort) {
        qWarning() << QCoreApplication::translate("QHttpServerExample",
                                                  "Server failed to listen on a port.");
        return -1;
    }

    qInfo().noquote()
        << QCoreApplication::translate("QHttpServerExample",
                                       "Running on http://127.0.0.1:%1/ and "
                                       "https://127.0.0.1:%2/ (Press CTRL+C to quit)")
               .arg(port).arg(sslPort);
#else
    qInfo().noquote()
        << QCoreApplication::translate("QHttpServerExample",
                                       "Running on http://127.0.0.1:%1/"
                                       "(Press CTRL+C to quit)").arg(port);
#endif
    return app.exec();
}
