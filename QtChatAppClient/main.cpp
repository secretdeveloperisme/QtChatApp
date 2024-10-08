#include "chatclient.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <messagelistmodel.h>

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

    ChatClient chatClient(&app);
    MessageListModel messageListModel(&chatClient);
    chatClient.setMessageListModel(&messageListModel);

    if (!chatClient.init()) {
        qCritical() << "Chat client could not be initialized";
        return -1;
    }

    // messageListModel.addMessage(Message(1,
    //                                     "hoanglinh",
    //                                     1,
    //                                     "Work",
    //                                     "this is message from Linh",
    //                                     QDateTime::currentDateTime()));
    // messageListModel.addMessage(Message(2,
    //                                     "thanhngueyn",
    //                                     1,
    //                                     "Work",
    //                                     "this is message from Thanh",
    //                                     QDateTime::currentDateTime()));
    engine.rootContext()->setContextProperty("messageListModel", &messageListModel);
    engine.rootContext()->setContextProperty("chatClient", &chatClient);
    engine.loadFromModule("QtChatAppClient", "Login");

    return app.exec();
}
