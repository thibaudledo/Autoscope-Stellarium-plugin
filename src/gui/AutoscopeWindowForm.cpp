#include "AutoscopeWindowForm.hpp"
#include "ui_AutoscopeWindowForm.h"
#include <QDesktopWidget>

AutoscopeWindowForm::AutoscopeWindowForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoscopeWindowForm)
{
    resize(600,300);
    QDesktopWidget screen;
    QRect screenSize = screen.screenGeometry();

    //qDebug() << "x:" << screenSize.width() << "y:" << screenSize.height();

    move(screenSize.width()- 600, screenSize.height()- 300);


    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    ui->setupUi(this);
}

AutoscopeWindowForm::~AutoscopeWindowForm()
{
    delete ui;
}
