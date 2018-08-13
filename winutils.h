#ifndef WINUTILS_H
#define WINUTILS_H
#include <QString>
#include <QPixmap>
#include <QIcon>
#include <Windows.h>
#include <QObject>
#include <QtWin>
#include <QDebug>
#include <QUrl>


static class WinUtils
{
public:
    static QString convertQTPath2WinPath(QString QTPath);
    static QPixmap getIconFromPEFile(HWND hwnd,HINSTANCE hInstance,LPCWSTR winPath);
    static QUrl convertPath2URL(QString path);
};

#endif // WINUTILS_H
