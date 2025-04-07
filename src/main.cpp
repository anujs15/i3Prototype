#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "i3connector.h"
#include "keyboardinterceptor.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    app.setOrganizationName("i3KeyboardInterceptor");
    app.setOrganizationDomain("i3KeyboardInterceptor");

    QQmlApplicationEngine engine;

    I3Connector *i3Connector = new I3Connector(&app);
    KeyboardInterceptor *keyboardInterceptor = new KeyboardInterceptor(&app);

    QObject::connect(keyboardInterceptor, &KeyboardInterceptor::keySequenceIntercepted,
                     i3Connector, &I3Connector::handleKeySequence);

    engine.rootContext()->setContextProperty("i3Connector", i3Connector);
    engine.rootContext()->setContextProperty("keyboardInterceptor", keyboardInterceptor);

    // Load the main QML file
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
