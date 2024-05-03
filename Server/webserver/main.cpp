#include <QCoreApplication>
#include "webapplication.h"

    using namespace Qt::StringLiterals;


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    WebApplication webApp;

    // Start the server
    webApp.startServer();
    return app.exec();
}
