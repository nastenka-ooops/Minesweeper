#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QDialog>

namespace Ui {
class CustomDialog;
}

class CustomDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomDialog(QWidget *parent = nullptr);
    ~CustomDialog();

private:
    Ui::CustomDialog *ui;
    bool isNeedSet;

private:
    void setDialogFlags();
    void connectButtoms();

public:
    void showDialog();
    void closeDialog();

public:
    bool getIsNeedSet();
    int getInputRows();
    int getInputCols();
    int getInputMineCount();
};

#endif // CUSTOMDIALOG_H
