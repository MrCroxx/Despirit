#include "winutils.h"

QString WinUtils::convertQTPath2WinPath(QString QTPath){
    QTPath.replace(QString("/"),QString("\\"));
    int pos = QTPath.indexOf(QChar(':'));
    if(pos>0){
        QTPath = QTPath.mid(pos-1);
    }
    return QTPath;
}

QPixmap WinUtils::getIconFromPEFile(HWND hwnd,HINSTANCE hInstance,LPCWSTR winPath){
    UINT count = ExtractIconExW(winPath, -1, NULL, NULL, 0);
    if(count<=0){
        QPixmap np;
        np.load(":/image/question_mark");
        return np;
    }
    qDebug()<<count;
    HICON hicon = ExtractIconW(hInstance,winPath,0);
    qDebug()<<"got hIcon";
    QPixmap p = QtWin::fromHICON(hicon);
    return p;
}

QUrl WinUtils::convertPath2URL(QString path){
    QString winPath = convertQTPath2WinPath(path);
    winPath.replace(QString("\\"),QString("/"));
    QString urlString = "file:///"+winPath;
    QUrl url = QUrl(urlString);
    return url;
}
