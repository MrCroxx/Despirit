#ifndef SPIRITSETTINGSFORM_H
#define SPIRITSETTINGSFORM_H

#include <QWidget>
#include <QDebug>
#include "settingsutils.h"

#include <QBitmap>

class FloatingWidget;

namespace Ui {
class SpiritSettingsForm;
}

class SpiritSettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SpiritSettingsForm(int id,FloatingWidget *spirit);
    ~SpiritSettingsForm();
protected:
    int id;
    FloatingWidget *spirit;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::SpiritSettingsForm *ui;
signals:
};

#endif // SPIRITSETTINGSFORM_H
