#include "settingsutils.h"

void SettingsUtils::checkSettings(){
    QSettings settings;
    if(!settings.contains("author")){
        qDebug()<<"settings not exists";
        initSettings();
    }
#ifndef QT_NO_DEBUG
    else{
        qDebug()<<"settings exists";
    }
#endif
}

void SettingsUtils::initSettings(){
    qDebug()<<"creating new settings";

    QString dataDirPath = appDataPath();
    QDir dir;
    if(!dir.exists(appDataPath())){
        dir.mkpath(appDataPath());
    }

    QSettings settings;
    settings.setValue("author","Croxx");
    settings.setValue("spirit_count",0);
    settings.setValue("spirits",QJsonArray());
}

QString SettingsUtils::appDataPath(){
    return QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
}

int SettingsUtils::addSpirit(){
    QSettings settings;
    QJsonArray spirits = settings.value("spirits").toJsonArray();
    int count = settings.value("spirit_count").toInt();

    QJsonObject spirit;
    spirit.insert("id",count);
    spirit.insert("x",0);
    spirit.insert("y",0);
    spirit.insert("shortcut_count",0);
    spirit.insert("shortcuts",QJsonArray());

    spirits.append(spirit);

    settings.setValue("spirits",spirits);
    settings.setValue("spirit_count",count+1);
    return count;
}

bool SettingsUtils::removeSpirit(int id){
    //TODO : REMOVE SHORTCUTS FILES
    bool found = false;
    QSettings settings;
    QJsonArray spirits = settings.value("spirits").toJsonArray();

    for(auto it = spirits.begin();it!=spirits.end();it++){
        auto spirit = (*it).toObject();
        if(spirit.value("id").toInt()==id){
            found = true;
            spirits.erase(it);
            break;
        }
    }
    settings.setValue("spirits",spirits);
    return found;
}

QList<int> SettingsUtils::getSpiritIds(){
    QSettings settings;
    QJsonArray spirits = settings.value("spirits").toJsonArray();
    QList<int> ids;
    for(auto it = spirits.begin();it!=spirits.end();it++){
        auto spirit = (*it).toObject();
        ids.append(spirit.value("id").toInt());
    }
    return ids;
}

bool SettingsUtils::setPosition(int id,QPoint pos){
    bool found = false;
    QSettings settings;
    QJsonArray spirits = settings.value("spirits").toJsonArray();

    for(auto it = spirits.begin();it!=spirits.end();it++){
        auto spirit = (*it).toObject();
        if(spirit.value("id").toInt()==id){
            found = true;
            spirit.insert("x",pos.x());
            spirit.insert("y",pos.y());
            *it = spirit;
            break;
        }
    }
    settings.setValue("spirits",spirits);
    return found;
}

QPoint SettingsUtils::getPosition(int id){
    QPoint pos(400,400);
    QSettings settings;
    QJsonArray spirits = settings.value("spirits").toJsonArray();

    for(auto it = spirits.begin();it!=spirits.end();it++){
        auto spirit = (*it).toObject();
        if(spirit.value("id").toInt()==id){
            pos.setX(spirit.value("x").toInt());
            pos.setY(spirit.value("y").toInt());
            break;
        }
    }
    return pos;
}

int SettingsUtils::addShortcut(int id,QString lnkPath,HWND hwnd,HINSTANCE hInstance){
    int found = -1;
    QSettings settings;
    QJsonArray spirits = settings.value("spirits").toJsonArray();

    for(auto it = spirits.begin();it!=spirits.end();it++){
        auto spirit = (*it).toObject();
        if(spirit.value("id").toInt()==id){
            int count = spirit.value("shortcut_count").toInt();
            found = count;

            lnkPath = WinUtils::convertQTPath2WinPath(lnkPath);

            QString lnkNewPath = WinUtils::convertQTPath2WinPath(appDataPath()+"/"+QString::number(id,10)+"_"+QString::number(count,10)+".lnk");
            QString iconNewPath = WinUtils::convertQTPath2WinPath(appDataPath()+"/"+QString::number(id,10)+"_"+QString::number(count,10)+".png");

            QFile::copy(lnkPath,lnkNewPath);
            QFileInfo info(lnkPath);
            QString targetPath = WinUtils::convertQTPath2WinPath(info.symLinkTarget());
            QPixmap icon = WinUtils::getIconFromPEFile(hwnd,hInstance,targetPath.toStdWString().c_str());
            icon.save(iconNewPath);

            QJsonObject shortcut;
            shortcut.insert("lnkPath",lnkNewPath);
            shortcut.insert("iconPath",iconNewPath);
            shortcut.insert("id",count);
            QJsonArray shortcuts = spirit.value("shortcuts").toArray();
            shortcuts.append(shortcut);

            spirit.insert("shortcuts",shortcuts);
            spirit.insert("shortcut_count",count+1);
            *it = spirit;
            break;
        }
    }
    settings.setValue("spirits",spirits);
    return found;
}

bool SettingsUtils::removeShortcut(int id,int sid){
    //TODO : NEED TEST
    bool found = false;
    QSettings settings;
    QJsonArray spirits = settings.value("spirits").toJsonArray();

    for(auto it = spirits.begin();it!=spirits.end();it++){
        auto spirit = (*it).toObject();
        if(spirit.value("id").toInt()==id){

            QJsonArray shortcuts = spirit.value("shortcuts").toArray();
            for(auto sit = shortcuts.begin();sit!=shortcuts.end();sit++){
                auto shortcut = (*sit).toObject();
                if(shortcut.value("id").toInt()==sid){
                    found = true;

                    QFile iconFile(shortcut.value("iconPath").toString());
                    QFile lnkFile(shortcut.value("lnkPath").toString());
                    if(iconFile.exists())iconFile.remove();
                    if(lnkFile.exists())lnkFile.remove();

                    shortcuts.erase(sit);
                }
            }

            *it = spirit;
            break;
        }
    }
    settings.setValue("spirits",spirits);
    return found;
}

QJsonArray SettingsUtils::getShortcuts(int id){
    QJsonArray shortcuts;
    QSettings settings;
    QJsonArray spirits = settings.value("spirits").toJsonArray();

    for(auto it = spirits.begin();it!=spirits.end();it++){
        auto spirit = (*it).toObject();
        if(spirit.value("id").toInt()==id){

            shortcuts = spirit.value("shortcuts").toArray();
            break;
        }
    }
    return shortcuts;
}
