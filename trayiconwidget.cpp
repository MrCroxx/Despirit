#include "trayiconwidget.h"

TrayIconWidget::TrayIconWidget(QWidget *parent) :
    QWidget(parent,Qt::FramelessWindowHint)
{
#ifndef QT_NO_DEBUG
    qDebug()<<"Debug Version Running...";
#endif
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setWindowFlag(Qt::Tool);
    this->setAcceptDrops(true);
    this->move(0,0);
    this->info = new infoForm();
    this->isShowing = true;
    createTrayIcon();
    showSpirits();
}

void TrayIconWidget::createTrayIcon(){
    createTrayMenu();
    if(!QSystemTrayIcon::isSystemTrayAvailable())return;
    trayIcon = new QSystemTrayIcon(this);
    QIcon icon(":/image/ghost_icon");
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("Despirit");
    trayIcon->setContextMenu(trayMenu);

    connect(trayIcon , SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));


    trayIcon->show();
}

void TrayIconWidget::createTrayMenu(){

    addSpiritAction = new QAction("New Spirit",this);
    quitAction = new QAction("Quit",this);

    infoAction = new QAction("@Croxx");


    connect(addSpiritAction,SIGNAL(triggered()),this,SLOT(addSpiritSlot()));
    connect(quitAction,SIGNAL(triggered()),qApp,SLOT(quit()));

    connect(infoAction,SIGNAL(triggered()),this,SLOT(showInfo()));

    trayMenu = new QMenu((QWidget*)QApplication::desktop());


    trayMenu->addAction(addSpiritAction);
    trayMenu->addSeparator();
    trayMenu->addAction(infoAction);
    trayMenu->addSeparator();
    trayMenu->addAction(quitAction);
}



void TrayIconWidget::addSpiritSlot(){
    int id = SettingsUtils::addSpirit();
    showFloatingWidget(id);
}

void TrayIconWidget::showFloatingWidget(int id){

    QPoint pos = SettingsUtils::getPosition(id);
    FloatingWidget *spirit = new FloatingWidget(id);
    spirit->move(pos);
    spirit->show();
    spirits.append(spirit);
}

void TrayIconWidget::showSpirits(){
    QList<int> ids = SettingsUtils::getSpiritIds();
    for(int i=0;i<ids.size();i++){
        showFloatingWidget(ids.at(i));
    }
}

void TrayIconWidget::hideAllSpirits(){
    this->isShowing = false;
    for(int i=0;i<spirits.size();i++){
        FloatingWidget *spirit = spirits.at(i);
        spirit->hide();
    }
}

void TrayIconWidget::showAllSpirits(){
    this->isShowing = true;
    for(int i=0;i<spirits.size();i++){
        FloatingWidget *spirit = spirits.at(i);
        if(spirit->inuse){
            qDebug()<<"show :"<<spirit->id;
            spirit->showNormal();
            spirit->raise();
            spirit->activateWindow();
        }
    }
}

void TrayIconWidget::showInfo(){
    this->info->show();
}

void TrayIconWidget::iconIsActived(QSystemTrayIcon::ActivationReason reason){
    switch(reason)
    {
    case QSystemTrayIcon::DoubleClick:
        if(this->isShowing){
            hideAllSpirits();
        }else{
            showAllSpirits();
        }
        break;

    }
}
