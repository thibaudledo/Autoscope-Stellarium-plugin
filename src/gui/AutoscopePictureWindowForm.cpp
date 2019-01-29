#include "AutoscopePictureWindowForm.hpp"
#include "ui_AutoscopePictureWindowForm.h"
#include "AutoscopeWindowForm.hpp"

#include "StelModule.hpp"
#include "StelModuleMgr.hpp"

#include <QDebug>

AutoscopePictureWindowForm::AutoscopePictureWindowForm()
    : StelDialog ("AutoscopePicture"),
    m_autoscope(Q_NULLPTR),
    m_autoscopeWindow(Q_NULLPTR)
{
    ui = new Ui_AutoscopePictureWindowForm();
}

AutoscopePictureWindowForm::~AutoscopePictureWindowForm()
{
    delete ui;
}

void AutoscopePictureWindowForm::update()
{

}

void AutoscopePictureWindowForm::createDialogContent()
{
    m_autoscope = GETSTELMODULE(Autoscope);

    ui->setupUi(dialog);

    m_screenWidth = m_autoscope->getScreenWidth();
    m_screenHeight = m_autoscope->getScreenHeight();

    m_guiHorizontalPosition = m_width;
    m_guiVerticalPosition = 0;

    dialog->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    dialog->resize(m_width, m_height);

    updateGuiPosition();
}

void AutoscopePictureWindowForm::retranslate()
{

}

int AutoscopePictureWindowForm::getGuiHorizontalPosition(void)
{
    return m_guiHorizontalPosition;
}

int AutoscopePictureWindowForm::getGuiVerticalPosition(void)
{
    return m_guiVerticalPosition;
}

void AutoscopePictureWindowForm::setGuiHorizontalPosition(int i)
{
    m_guiHorizontalPosition = i;
    updateGuiPosition();
}

void AutoscopePictureWindowForm::setGuiVerticalPosition(int i)
{
    m_guiVerticalPosition = i;
    updateGuiPosition();
}

int AutoscopePictureWindowForm::getGuiWidth(void)
{
    return m_width;
}

int AutoscopePictureWindowForm::getGuiHeight(void)
{
    return m_height;
}

void AutoscopePictureWindowForm::setGuiSize(int percent)
{
    qDebug() << "percent :" << percent;
    m_width = int((m_screenWidth * percent)/100);
    m_height = int((m_screenHeight * percent)/100);
    qDebug() << "size :" << m_width << " "  << m_height;

    updateGuiSize();
}

void AutoscopePictureWindowForm::updateGuiSize(void)
{
    qDebug() << "updateGuiSize";
    dialog->resize(m_width, m_height);
    updateGuiPosition();
}

void AutoscopePictureWindowForm::setGuiOpacity(double opacity)
{
    qDebug() << "setGuiOpacity";
    dialog->setWindowOpacity(opacity);
}

void AutoscopePictureWindowForm::updateGuiPosition(void)
{
    qDebug() << "updateGuiPosition";

    dialog->move(int(m_screenWidth-m_guiHorizontalPosition), int(m_guiVerticalPosition));
}

void AutoscopePictureWindowForm::updateImage(QPixmap image)
{
    ui->pictureDisplayLabel->setPixmap(image.scaled(m_width, m_height, Qt::KeepAspectRatio));
}
