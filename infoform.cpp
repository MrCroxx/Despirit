#include "infoform.h"
#include "ui_infoform.h"

infoForm::infoForm(QWidget *parent) :
    QWidget(parent,Qt::FramelessWindowHint),
    ui(new Ui::infoForm)
{
    ui->setupUi(this);
    this->setFixedSize(240,100);
    QPixmap bgImages(":/image/cloth_background");
    QPalette bgPalette = this->palette();
    bgPalette.setBrush(QPalette::Background,bgImages);
    this->setPalette(bgPalette);
    setMask(bgImages.mask());
}

infoForm::~infoForm()
{
    delete ui;
}

void infoForm::on_pushButton_clicked()
{
    this->hide();
}
