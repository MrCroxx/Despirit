#include "shortcutwidget.h"

ShortcutWidget::ShortcutWidget(int id,int sid,QString lnkPath,QString iconPath,QSize size,QWidget *parent) :
    QWidget(parent,Qt::FramelessWindowHint),
    id(id),sid(sid),
    lnkPath(lnkPath),iconPath(iconPath)
{
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setWindowFlag(Qt::Tool);
    this->setAcceptDrops(true);
    this->resize(size);
    this->icon.load(iconPath);
}

void ShortcutWidget::mouseReleaseEvent(QMouseEvent *event){
    qDebug()<<"run : "<<this->lnkPath;
}

void ShortcutWidget::paintEvent(QPaintEvent *event){
    int w = this->width();
    int h = this->height();
    QPainter painter(this);
    painter.drawPixmap(w/2,h/2,w,h,icon);
}
