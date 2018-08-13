#ifndef BASICWIDGET_H
#define BASICWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>

class BasicWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BasicWidget(QWidget *parent = nullptr);
    ~BasicWidget();
protected:
    void paintEvent(QPaintEvent *);

};

#endif // BASICWIDGET_H
