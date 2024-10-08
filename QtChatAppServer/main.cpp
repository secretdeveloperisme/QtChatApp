#include "../QtChatAppClient/messagelistmodel.h"
#include "chatserver.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    ChatServer chatserver;
    engine.rootContext()->setContextProperty("server", &chatserver);
    engine.loadFromModule("QtChatAppServer", "Main");

    return app.exec();
}
