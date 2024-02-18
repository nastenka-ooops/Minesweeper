#ifndef SUCCESSDIALOG_H
#define SUCCESSDIALOG_H

#include <QDialog>

namespace Ui {
class SuccessDialog;
}

class SuccessDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SuccessDialog(QWidget *parent = nullptr);
    ~SuccessDialog();

private:
    Ui::SuccessDialog *ui;
    bool isNeedSave;

private:
    void setDialogFlags();
    void connectButtoms();

public:
    void showDialog();
    void closeDialog();

public:
    bool getIsNeedSave();
    QString getInputName();
};

#endif // SUCCESSDIALOG_H
