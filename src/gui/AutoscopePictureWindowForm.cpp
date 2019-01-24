#include "AutoscopePictureWindowForm.hpp"
#include "ui_AutoscopePictureWindowForm.h"
#include "AutoscopeWindowForm.hpp"

#include "StelModule.hpp"
#include "StelModuleMgr.hpp"

#include <QDebug>

AutoscopePictureWindowForm::AutoscopePictureWindowForm(AutoscopeWindowForm* autoscopeWindowForm)
    : StelDialog ("AutoscopePicture"),
    m_autoscope(Q_NULLPTR),
    m_autoscopeWindow(Q_NULLPTR)
{
    ui = new Ui_AutoscopePictureWindowForm();
    m_autoscopeWindow = autoscopeWindowForm;
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
    //m_autoscopeWindow = GETSTELMODULE(AutoscopeWindowForm);

    ui->setupUi(dialog);

    m_screenWidth = m_autoscopeWindow->getScreenWidth();
    m_screenHeight = m_autoscopeWindow->getScreenHeight();

    m_guiHorizontalPosition = 0;
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
    dialog->resize(m_width, m_height);
    updateGuiPosition();
}

void AutoscopePictureWindowForm::setGuiOpacity(double opacity)
{
    dialog->setWindowOpacity(opacity);
}

void AutoscopePictureWindowForm::updateGuiPosition(void)
{
    dialog->move(int(m_screenWidth-m_width-m_guiHorizontalPosition), int(m_guiVerticalPosition));
}

void AutoscopePictureWindowForm::updateImage(QPixmap image)
{
    ui->pictureDisplayLabel->setPixmap(image.scaled(m_width, m_height, Qt::KeepAspectRatio));
}
