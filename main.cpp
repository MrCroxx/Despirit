#include "floatingwidget.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QStandardPaths>
#include <QSettings>
#include <QCoreApplication>
#include "trayiconwidget.h"
#include "settingsutils.h"

bool readJsonFile(QIODevice &device, QSettings::SettingsMap &map)
{
    bool ret = false;

    QJsonParseError error;
    map = QJsonDocument::fromJson(device.readAll() , &error).toVariant().toMap();

    if( error.error == QJsonParseError::NoError )
        ret = true;

    return ret;
}

bool writeJsonFile(QIODevice &device, const QSettings::SettingsMap &map)
{
    bool ret = false;

    QJsonDocument jsonDocument = QJsonDocument::fromVariant(QVariant::fromValue(map));
    if ( device.write(jsonDocument.toJson()) != -1 )
        ret = true;

    return ret;
}

int main(int argc, char *argv[])
{

    QCoreApplication::setOrganizationName("Croxx");
    QCoreApplication::setOrganizationDomain("croxx.xyz");
    QCoreApplication::setApplicationName("Despirit");
    const QSettings::Format JsonFormat = QSettings::registerFormat("json",readJsonFile,writeJsonFile);
    QSettings::setDefaultFormat(JsonFormat);

    SettingsUtils::checkSettings();

    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false);
    TrayIconWidget t;
    t.show();

    return a.exec();

}
