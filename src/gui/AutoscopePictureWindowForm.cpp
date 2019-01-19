#include "AutoscopePictureWindowForm.hpp"
#include "ui_AutoscopePictureWindowForm.h"
#include "AutoscopeWindowForm.hpp"

#include <QDebug>

AutoscopePictureWindowForm::AutoscopePictureWindowForm(QWidget *parent, Autoscope* autoscope, AutoscopeWindowForm* autoscopeWindow, int screenWidth, int screenHeight) :
    QWidget(parent),
    ui(new Ui::AutoscopePictureWindowForm)
{
    m_autoscope = autoscope;
    m_autoscopeWindow = autoscopeWindow;

    ui->setupUi(this);

    m_screenWidth = screenWidth;
    m_screenHeight = screenHeight;

    resize(m_width, m_height);

    qDebug() << "size:" << m_screenWidth << " "  << m_screenHeight;

    qDebug() << "size :" << m_width << " "  << m_height;

    m_guiHorizontalPosition = m_screenWidth - m_width;
    m_guiVerticalPosition = 10;

    qDebug() << "position :" << m_guiHorizontalPosition << " "  << m_guiVerticalPosition;

    move(m_guiHorizontalPosition, m_guiVerticalPosition);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);


}

AutoscopePictureWindowForm::~AutoscopePictureWindowForm()
{
    delete ui;
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
    resize(m_width, m_height);
    updateGuiPosition();
}

void AutoscopePictureWindowForm::setGuiOpacity(double opacity)
{
    setWindowOpacity(opacity);
}

void AutoscopePictureWindowForm::updateGuiPosition(void)
{
    move(int(m_guiHorizontalPosition), int(m_guiVerticalPosition));
}
