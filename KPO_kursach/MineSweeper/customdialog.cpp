#include "customdialog.h"
#include "ui_customdialog.h"

CustomDialog::CustomDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CustomDialog)
{
    ui->setupUi(this);
    setDialogFlags();
    connectButtoms();
}

CustomDialog::~CustomDialog()
{
    delete ui;
}

void CustomDialog::setDialogFlags(){
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);
}

void CustomDialog::connectButtoms(){
    connect(ui->pDoneButton, &QPushButton::clicked, this, &CustomDialog::closeDialog);
}

void CustomDialog::showDialog(){
    isNeedSet = false;
    QDialog::exec();
}
void CustomDialog::closeDialog(){
    isNeedSet=true;
    QDialog::close();
}

bool CustomDialog::getIsNeedSet(){
    return isNeedSet;
}

int CustomDialog::getInputRows(){
    return ui->pRowsNumberSpinBox->value();
}

int CustomDialog::getInputCols(){
    return ui->pColsNumberSpinBox->value();
}


int CustomDialog::getInputMineCount(){
    if(ui->pMinesNumberSpinBox->value()>=ui->pColsNumberSpinBox->value()*ui->pRowsNumberSpinBox->value()){
    return ui->pColsNumberSpinBox->value()*ui->pRowsNumberSpinBox->value()-1;
    } else{
    return ui->pMinesNumberSpinBox->value();
    }
}
