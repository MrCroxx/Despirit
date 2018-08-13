#include "spiritsettingsform.h"
#include "ui_spiritsettingsform.h"

#include "floatingwidget.h"

SpiritSettingsForm::SpiritSettingsForm(int id,FloatingWidget *spirit) :
    QWidget(nullptr,Qt::FramelessWindowHint),id(id),
    ui(new Ui::SpiritSettingsForm)
{
    ui->setupUi(this);
    this->setFixedSize(200,100);
    this->spirit = spirit;
    QPixmap bgImages(":/image/cloth_background");
    QPalette bgPalette = this->palette();
    bgPalette.setBrush(QPalette::Background,bgImages);
    this->setPalette(bgPalette);
    setMask(bgImages.mask());
}

SpiritSettingsForm::~SpiritSettingsForm()
{
    delete ui;
}

void SpiritSettingsForm::on_pushButton_clicked()
{
    // Cancel
    this->hide();
}

void SpiritSettingsForm::on_pushButton_2_clicked()
{
    // Delete
    SettingsUtils::removeSpirit(spirit->id);
    spirit->inuse=false;
    spirit->hide();
    this->hide();
}
