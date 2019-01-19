#include "AutoscopeWindowForm.hpp"
#include "ui_AutoscopeWindowForm.h"
#include <QDesktopWidget>
#include <QDebug>

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
    //setStyleSheet(getStyleSheet());

    ui->setupUi(this);
}

AutoscopeWindowForm::~AutoscopeWindowForm()
{
    delete ui;
}

QString AutoscopeWindowForm::getStyleSheet()
{
    QString steelsheet =
            " QWidget{background-color: #24282B;}"
            " QTabWidget{color: #9EA097; background-color: #4B4C4F;}"
            " QPushButton{color: #292A2B; background-color: #8A8B8C;}";
    return steelsheet;
}
