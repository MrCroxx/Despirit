#ifndef SHORTCUTWIDGET_H
#define SHORTCUTWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QSize>
#include <QPixmap>
#include "settingsutils.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>

class ShortcutWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ShortcutWidget(int id,int sid,QString lnkPath,QString iconPath,QSize size,QWidget *parent = nullptr);
protected:
    QString iconPath;
    QString lnkPath;
    int id;
    int sid;
    QPixmap icon;
    void mouseReleaseEvent(QMouseEvent*);
    void paintEvent(QPaintEvent *);

private:

signals:

public slots:
};

#endif // SHORTCUTWIDGET_H
