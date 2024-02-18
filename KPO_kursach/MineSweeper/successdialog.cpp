#include "successdialog.h"
#include "ui_successdialog.h"

SuccessDialog::SuccessDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SuccessDialog)
{
    ui->setupUi(this);
    setDialogFlags();
    connectButtoms();
}

SuccessDialog::~SuccessDialog()
{
    delete ui;
}

void SuccessDialog::setDialogFlags(){
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}

void SuccessDialog::connectButtoms(){
    connect(ui->pDoneButton, &QPushButton::clicked, this, &SuccessDialog::closeDialog);
}

void SuccessDialog::showDialog(){
    isNeedSave = false;
    QDialog::exec();
}
void SuccessDialog::closeDialog(){
    isNeedSave=true;
    QDialog::close();
}

bool SuccessDialog::getIsNeedSave(){
    return isNeedSave;
}

QString SuccessDialog::getInputName(){
    return ui->pNameEdit->text();
}
