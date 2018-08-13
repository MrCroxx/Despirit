#include "floatingwidget.h"
#include "spiritsettingsform.h"

FloatingWidget::FloatingWidget(int id,QWidget *parent) :
    QWidget(parent,Qt::FramelessWindowHint),
    relativePos(0,0),
    id(id),icon(),showshortcuts(false),shortcuts(),inuse(true)
{
    // Set Basic Properties

    this->setAttribute(Qt::WA_TranslucentBackground,true);
    this->setWindowFlag(Qt::Tool);
    this->setAcceptDrops(true);
    this->resize(this->W,this->H);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);

    // Init icon

    iconPath = SettingsUtils::appDataPath()+"/"+QString::number(id,10)+".png";
    QFile iconFile(iconPath);
    if(!iconFile.exists()){
        icon.load(":/image/ghost");
        icon.save(iconPath);
    }else{
        icon.load(iconPath);
    }

    // Init Timers

    mouseOutTimer = new QTimer(this);
    mouseOutTimer->setSingleShot(true);
    connect(mouseOutTimer,SIGNAL(timeout()),this,SLOT(mouseOut3s()));

    // Init SettingsForm
    form = new SpiritSettingsForm(this->id,this);

}

void FloatingWidget::paintEvent(QPaintEvent *){

    QPainter iconPainter(this);
    iconPainter.setOpacity(this->ALPHA);
    iconPainter.setRenderHint(QPainter::Antialiasing);
    iconPainter.setRenderHint(QPainter::SmoothPixmapTransform);

    iconPainter.drawPixmap(this->OX-this->OW/2,this->OY-this->OH/2,this->OW,this->OH,icon);

    QPainter shortcutPainter(this);
    shortcutPainter.setOpacity(this->ALPHA);
    shortcutPainter.setRenderHint(QPainter::Antialiasing);
    shortcutPainter.setRenderHint(QPainter::SmoothPixmapTransform);



    if(this->showshortcuts){
        QJsonArray shortcuts = SettingsUtils::getShortcuts(this->id);
        int count = shortcuts.size();
        double deltaAngle = 2 * PI / count;
        for(int i=0;i<count;i++){
            QJsonObject shortcut = shortcuts.at(i).toObject();
            double deltaX = std::sin(deltaAngle*i)*this->RADIUS;
            double deltaY = 0 - std::cos(deltaAngle*i)*this->RADIUS;
            qDebug()<<i<<":"<<deltaX<<","<<deltaY<<"----"<<this->RADIUS;
            QPixmap shortcutIcon;
            shortcutIcon.load(shortcut.value("iconPath").toString());
            shortcutPainter.drawPixmap(this->OX+deltaX-this->CW/2,this->OY+deltaY-this->CH/2,this->CW,this->CH,shortcutIcon);
        }
    }



}

void FloatingWidget::enterEvent(QEvent *){
    qDebug()<<"enter";
    showShortcuts();
    if(mouseOutTimer->isActive())mouseOutTimer->stop();
}

void FloatingWidget::leaveEvent(QEvent *){
    qDebug()<<"leave";
    mouseOutTimer->start(1000);
}

void FloatingWidget::mouseMoveEvent(QMouseEvent *event){
    this->move(event->globalPos() + relativePos);
}

void FloatingWidget::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::LeftButton){
        relativePos = this->pos() - event->globalPos();
    }
}

void FloatingWidget::mouseReleaseEvent(QMouseEvent *event){
    SettingsUtils::setPosition(this->id,event->globalPos() + relativePos);

    QPoint pos = event->localPos().toPoint()-QPoint(this->OX,this->OY);
    int dis2 = pos.x()*pos.x()+pos.y()*pos.y();


    if(dis2>this->DIAGR2){
        QJsonArray shortcuts = SettingsUtils::getShortcuts(this->id);
        int count = shortcuts.size();
        int angle = std::round(std::atan2(pos.y(),pos.x())/this->PI*180);
        angle = (angle+450)%360;
        int angleOffset =(angle+360/count/2)%360;
        int offset = (double)angleOffset/(360/(double)count);
        QJsonObject shortcut = shortcuts.at(offset).toObject();
        QString lnkPath = shortcut.value("lnkPath").toString();
        QUrl url = WinUtils::convertPath2URL(lnkPath);
        QDesktopServices::openUrl(url);
    }
    qDebug()<<"release[ pos:"<<pos<<" dis2:"<<dis2<<" DIAGR2:"<<this->DIAGR2<<" ]";
    qDebug()<<this->id;
}

void FloatingWidget::dragEnterEvent(QDragEnterEvent *event){
    qDebug()<<"drag enter";

    bool flag = true;
    QList<QUrl> urls = event->mimeData()->urls();
    for(QUrl url:urls){
        QFileInfo info(url.path());
        if(!info.isSymLink()&&info.suffix()!="png")
            flag = false;
    }
    if(flag)
        event->acceptProposedAction();
}

void FloatingWidget::dropEvent(QDropEvent *event){
    qDebug()<<"drop";
    QList<QUrl> urls = event->mimeData()->urls();
    for(QUrl url:urls){
        QString path = WinUtils::convertQTPath2WinPath(url.path());
        QFileInfo info(path);
        qDebug()<<"is symlink : "<<info.isSymLink()<<", link target : "<<info.symLinkTarget();
        if(info.isSymLink()){
            HWND hwnd = (HWND)this->winId();
            HINSTANCE hInstance = (HINSTANCE)::GetModuleHandle(NULL);
            SettingsUtils::addShortcut(this->id,path,hwnd,hInstance);
        }else if(info.suffix()=="png"){
            qDebug()<<"modify icon";
            this->modifyIcon(path);
        }

    }
}

void FloatingWidget::mouseDoubleClickEvent(QMouseEvent *){
    form->show();
    /*
    SettingsUtils::removeSpirit(this->id);
    this->inuse=false;
    this->hide();
    */
}

void FloatingWidget::showShortcuts(){
    this->showshortcuts=true;
    this->update();
}

void FloatingWidget::hideShortcuts(){
    this->showshortcuts=false;
    this->update();
}

void FloatingWidget::mouseOut3s(){
    qDebug()<<"timer slot";
    this->hideShortcuts();
}

void FloatingWidget::hideEvent(QHideEvent *){
    qDebug()<<"hide "<<this->id;
}

void FloatingWidget::modifyIcon(QString path){
    QString iconPath = SettingsUtils::appDataPath()+"/"+QString::number(this->id,10)+".png";
    QFile(iconPath).remove();
    QFile::copy(path,iconPath);
    this->icon.load(iconPath);
    this->update();
}

