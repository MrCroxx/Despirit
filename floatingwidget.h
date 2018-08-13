#ifndef FLOATINGWIDGET_H
#define FLOATINGWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPointer>
#include <QEvent>
#include <QDebug>
#include <QPainter>
#include <QMouseEvent>
#include <QPoint>
#include <QBitmap>
#include <QDropEvent>
#include <QList>
#include <QUrl>
#include <QFile>
#include <QFileInfo>
#include <QMimeData>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QLabel>
#include <QDir>
#include <QDesktopServices>
#include <QIcon>
#include <QFileIconProvider>
#include <QFileSystemModel>
#include <QMimeDatabase>
#include <QMimeType>
#include <qt_windows.h>
#include <QtWinExtras/QtWin>
#include <QtWinExtras/QtWinExtras>
#include <Windows.h>
#include "winutils.h"
#include <cmath>
#include "settingsutils.h"
#include <iostream>
#include "shortcutwidget.h"

#include <QHideEvent>

class SpiritSettingsForm;

class FloatingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FloatingWidget(int id,QWidget *parent = nullptr);
    bool inuse;
    int id;
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void dragEnterEvent(QDragEnterEvent *);
    void dropEvent(QDropEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void hideEvent(QHideEvent *);


    void showShortcuts();
    void hideShortcuts();
    void modifyIcon(QString path);

    QPoint relativePos;

    QString iconPath;
    QPixmap icon;
    SpiritSettingsForm *form;

    const qreal ALPHA = 0.8;

    const double RADIUS = 100;
    const double PI = 3.1415;
    const int OX = 400;
    const int OY = 400;
    const int OW = 75;
    const int OH = 75;
    const int CW = 50;
    const int CH = 50;
    const int W = std::max((int)(OX+OW/2),(int)(OX+RADIUS+CW/2));
    const int H = std::max((int)(OY+OH/2),(int)(OY+RADIUS+CH/2));
    const int DIAGR2 = (OW*OW+OH*OH)/4;
    bool showshortcuts;
    QTimer *mouseOutTimer;
    QList<ShortcutWidget*> shortcuts;

private:

signals:

public slots:
    void mouseOut3s();
};

#endif // FLOATINGWIDGET_H
