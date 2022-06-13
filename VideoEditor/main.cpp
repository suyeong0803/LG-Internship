#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "VideoEditorViewModel.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    VideoEditorViewModel ve;
    //qmlRegisterType<VideoEditorViewModel>("ViewModel",1,0,"VideoEditorViewModel");
    engine.rootContext()->setContextProperty("VideoEditorViewModel", &ve);
    const QUrl url(u"qrc:/VideoEditor/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
