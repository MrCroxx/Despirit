#ifndef SETTINGSUTILS_H
#define SETTINGSUTILS_H

#include <QSettings>
#include <QDebug>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>
#include <QStandardPaths>
#include <QDir>
#include <QPoint>
#include <QList>
#include <QFile>
#include <QFileInfo>
#include <Windows.h>
#include "winutils.h"

static class SettingsUtils
{
public:
    static void checkSettings();
    static void initSettings();
    static QString appDataPath();
    static int addSpirit();
    static bool removeSpirit(int id);
    static QList<int> getSpiritIds();
    static bool setPosition(int id,QPoint pos);
    static QPoint getPosition(int id);
    static int addShortcut(int id,QString lnkPath,HWND hwnd,HINSTANCE hInstance);
    static bool removeShortcut(int id,int sid);
    static QJsonArray getShortcuts(int id);



};

#endif // SETTINGSUTILS_H
