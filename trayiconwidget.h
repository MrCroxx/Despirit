#ifndef TRAYICONWIDGET_H
#define TRAYICONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QApplication>
#include <QAction>
#include "floatingwidget.h"
#include <QList>
#include "settingsutils.h"
#include "infoform.h"
#include <QSystemTrayIcon>

class TrayIconWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TrayIconWidget(QWidget *parent = nullptr);
protected:
    QSystemTrayIcon *trayIcon;
    QMenu *trayMenu;
    QAction *addSpiritAction;
    QAction *quitAction;
    QAction *infoAction;

    infoForm *info;
    bool isShowing;

    void createTrayIcon();
    void createTrayMenu();
    void showFloatingWidget(int id);
    void showSpirits();    
    QList<FloatingWidget*>spirits;
private:

signals:

public slots:
    void addSpiritSlot();
    void showAllSpirits();
    void hideAllSpirits();
    void iconIsActived(QSystemTrayIcon::ActivationReason reason);
    void showInfo();
};

#endif // TRAYICONWIDGET_H
