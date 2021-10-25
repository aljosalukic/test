#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "VideoItemsModel.h"
#include "Utils.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    Utils::getInstance()->initDirectories();

    qmlRegisterType<VideoItemsModel>("Model", 1, 0, "VideoItemsModel");
    qmlRegisterType<Utils>("UtilsModel", 1, 0, "Utils");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
