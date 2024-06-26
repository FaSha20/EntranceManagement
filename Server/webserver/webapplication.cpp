#include "webapplication.h"

WebApplication::WebApplication(QObject *parent)
    : QObject(parent), port(8083), socket(port, true)
{}

WebApplication::~WebApplication()
{
    // Destructor
}

bool WebApplication::startServer()
{
    // Start the HTTP server
    return httpserver.startServer();
}
