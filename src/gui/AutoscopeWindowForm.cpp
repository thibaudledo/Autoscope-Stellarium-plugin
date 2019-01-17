#include "AutoscopeWindowForm.hpp"
#include "ui_AutoscopeWindowForm.h"

AutoscopeWindowForm::AutoscopeWindowForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoscopeWindowForm)
{
    ui->setupUi(this);
}

AutoscopeWindowForm::~AutoscopeWindowForm()
{
    delete ui;
}
