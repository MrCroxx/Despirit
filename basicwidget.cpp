#include "basicwidget.h"

BasicWidget::BasicWidget(QWidget *parent) :
    QWidget(parent,Qt::FramelessWindowHint)
{
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setWindowFlag(Qt::Tool);
    this->move(0,0);

#ifndef QT_NO_DEBUG
    //Debug版程序，显示Debug Label
    QLabel *label = new QLabel(this);
    label->setText(QObject::tr("程序已经启动!"));
    label->resize(180,20);
#endif



}

BasicWidget::~BasicWidget()
{

}

void BasicWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.drawLine(0,0,100,100);
}
