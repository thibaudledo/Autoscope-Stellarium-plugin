#include "AutoscopeWindow.hpp"
#include "ui_AutoscopeWindow.h"

AutoscopeWindow::AutoscopeWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoscopeWindow)
{
    ui->setupUi(this);
}

AutoscopeWindow::~AutoscopeWindow()
{
    delete ui;
}
