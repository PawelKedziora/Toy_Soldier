#include "uiform.h"
#include "ui_UiForm.h"

UiForm::UiForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

UiForm::~UiForm()
{
    delete ui;
}
