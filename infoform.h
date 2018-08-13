#ifndef INFOFORM_H
#define INFOFORM_H

#include <QWidget>
#include <QBitmap>

namespace Ui {
class infoForm;
}

class infoForm : public QWidget
{
    Q_OBJECT

public:
    explicit infoForm(QWidget *parent = nullptr);
    ~infoForm();

private slots:
    void on_pushButton_clicked();

private:
    Ui::infoForm *ui;
};

#endif // INFOFORM_H
