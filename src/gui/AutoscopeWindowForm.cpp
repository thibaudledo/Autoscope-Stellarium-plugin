#include "AutoscopeWindowForm.hpp"
#include "ui_AutoscopeWindowForm.h"
#include <QDesktopWidget>
#include <QDebug>

#include <QFileDialog>
#include "AutoscopePictureWindowForm.hpp"

class Autoscope;

AutoscopeWindowForm::AutoscopeWindowForm(QWidget *parent, Autoscope* autoscope) :
    QWidget(parent),
    ui(new Ui::AutoscopeWindowForm)
{
    m_autoscope = autoscope;

    resize(m_width, m_height);
    QDesktopWidget screen;
    QRect screenSize = screen.screenGeometry();

    m_screenWidth = screenSize.width();
    m_screenHeight = screenSize.height();

    m_autoscopePictureWindow = new AutoscopePictureWindowForm(nullptr, m_autoscope, this, m_screenWidth, m_screenHeight);

    m_guiHorizontalPosition = m_screenWidth - m_width;
    m_guiVerticalPosition = m_screenHeight - m_height;

    move(m_guiHorizontalPosition, m_guiVerticalPosition);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    ui->setupUi(this);

    ui->verticalDisplayPositionEditor->setMaximum(m_screenHeight);
    ui->verticalDisplayPositionEditor->setValue(m_autoscopePictureWindow->getGuiVerticalPosition());

    ui->horizontalDisplayPositionEditor->setMaximum(m_screenWidth);
    ui->horizontalDisplayPositionEditor->setValue(m_autoscopePictureWindow->getGuiHorizontalPosition());

    ui->picurePathButton->setIcon(QPixmap(":/Autoscope/dossier.png"));

    connect(ui->moveToButton, SIGNAL(clicked()), this, SLOT(moveToButtonPressed()));
    connect(ui->azimuthEditor, SIGNAL(valueChanged(double)), this, SLOT(azimuthChanged(double)));
    connect(ui->altitudeEditor, SIGNAL(valueChanged(double)), this, SLOT(altitudeChanged(double)));
    connect(ui->searchEditor, SIGNAL(textChanged(QString)), this, SLOT(searchObjectChanged(QString)));
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(searchButtonPressed(void)));
    connect(ui->zoomEditor, SIGNAL(valueChanged(int)), this, SLOT(zoomChanged(int)));
    connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoomChanged(int)));
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startButtonPressed(void)));
    connect(ui->trackButton, SIGNAL(clicked()), this, SLOT(trackButtonPressed(void)));
    connect(ui->untrackButton, SIGNAL(clicked()), this, SLOT(untrackButtonPressed(void)));
    connect(ui->takePictureButton, SIGNAL(clicked()), this, SLOT(takePictureButtonPressed(void)));
    connect(ui->toggleDisplayButton, SIGNAL(clicked()), this, SLOT(toggleDisplayButtonPressed(void)));
    connect(ui->exposureTimeEditor, SIGNAL(valueChanged(double)), this, SLOT(exposureTimeChanged(double)));
    connect(ui->numberPictureEditor, SIGNAL(valueChanged(int)), this, SLOT(numberOfPictureChanged(int)));
    connect(ui->displaySizeEditor, SIGNAL(valueChanged(int)), this, SLOT(displaySizeChanged(int)));
    connect(ui->horizontalDisplayPositionEditor, SIGNAL(valueChanged(int)), this, SLOT(horizontalDisplayPositionChanged(int)));
    connect(ui->verticalDisplayPositionEditor, SIGNAL(valueChanged(int)), this, SLOT(verticalDisplayPositionChanged(int)));
    connect(ui->displayOpacityEditor, SIGNAL(valueChanged(double)), this, SLOT(displayOpacityChanged(double)));
    connect(ui->picturePathEditor, SIGNAL(returnPressed()), this, SLOT(outputPictureDirectoryChanged(void)));
    connect(ui->picurePathButton, SIGNAL(clicked()), this, SLOT(outputPictureDirectoryButtonPressed(void)));
    connect(ui->pictureDownloadButton, SIGNAL(clicked()), this, SLOT(downloadPictureButtonPressed(void)));
}

AutoscopeWindowForm::~AutoscopeWindowForm()
{
    delete ui;
}

int AutoscopeWindowForm::getGuiHorizontalPosition(void)
{
    return m_guiHorizontalPosition;
}

int AutoscopeWindowForm::getGuiVerticalPosition(void)
{
    return m_guiVerticalPosition;
}

int AutoscopeWindowForm::getScreenSizePercent(void)
{
    return ui->displaySizeEditor->value();
}

//  Public slots:

void AutoscopeWindowForm::startButtonPressed(void)
{
    qDebug() << "startButtonPressed";
}

void AutoscopeWindowForm::trackButtonPressed(void)
{
    qDebug() << "trackButtonPressed";
    m_autoscope->trackSelectedObject();
}

void AutoscopeWindowForm::untrackButtonPressed(void)
{
    qDebug() << "untrackButtonPressed";
    m_autoscope->clearTrackedObject();
}

void AutoscopeWindowForm::takePictureButtonPressed(void)
{
    qDebug() << "takePictureButtonPressed";
}

void AutoscopeWindowForm::toggleDisplayButtonPressed(void)
{
    qDebug() << "toggleDisplayButtonPressed";

    if(pictureWindowIsVisible)
    {
        m_autoscopePictureWindow->setVisible(false);
        pictureWindowIsVisible = false;
    }else{
        m_autoscopePictureWindow->setVisible(true);
        pictureWindowIsVisible = true;
    }
}

//  Private slots:

void AutoscopeWindowForm::moveToButtonPressed(void)
{
    qDebug() << "moveToButtonPressed";
}

void AutoscopeWindowForm::azimuthChanged(double d)
{
    qDebug() << "azimuthChanged";
}

void AutoscopeWindowForm::altitudeChanged(double d)
{
    qDebug() << "altitudeChanged";
}

void AutoscopeWindowForm::searchObjectChanged(QString s)
{
    qDebug() << "searchObjectChanged";
    if(s!="")
    {
        ui->searchEditorMessenger->setText(m_autoscope->searchAnObject(s));
    }else{
        ui->searchEditorMessenger->setText("");
    }
}

void AutoscopeWindowForm::searchButtonPressed(void)
{
    qDebug() << "searchButtonPressed";
    ui->searchEditorMessenger->setText(m_autoscope->trackSearchedObject());
}

void AutoscopeWindowForm::zoomChanged(int i)
{
    qDebug() << "zoomChanged";
}

void AutoscopeWindowForm::exposureTimeChanged(double d)
{
    qDebug() << "exposureTimeChanged";
}

void AutoscopeWindowForm::numberOfPictureChanged(int i)
{
    qDebug() << "numberOfPictureChanged";
}

void AutoscopeWindowForm::displaySizeChanged(int percent)
{
    qDebug() << "displaySizeChanged";
    m_autoscopePictureWindow->setGuiSize(percent);

    ui->horizontalDisplayPositionEditor->setMaximum(int(m_screenWidth-(m_autoscopePictureWindow->getGuiWidth())));
    ui->verticalDisplayPositionEditor->setMaximum(int(m_screenHeight-(m_autoscopePictureWindow->getGuiHeight())));
}

void AutoscopeWindowForm::horizontalDisplayPositionChanged(int x)
{
    qDebug() << "horizontalDisplayPositionChanged";
    m_autoscopePictureWindow->setGuiHorizontalPosition(x);
}

void AutoscopeWindowForm::verticalDisplayPositionChanged(int y)
{
    qDebug() << "verticalDisplayPositionChanged";
    m_autoscopePictureWindow->setGuiVerticalPosition(y);
}

void AutoscopeWindowForm::displayOpacityChanged(double opacity)
{
    qDebug() << "displayOpacityChanged";
    m_autoscopePictureWindow->setGuiOpacity(opacity);
}

void AutoscopeWindowForm::outputPictureDirectoryChanged(void)
{
    qDebug() << "outputPictureDirectoryChanged";
}

void AutoscopeWindowForm::outputPictureDirectoryButtonPressed(void)
{
    qDebug() << "outputPictureDirectoryButtonPressed";
    picturedirectoryPath = QFileDialog::getExistingDirectory(nullptr);
    ui->picturePathEditor->setText(picturedirectoryPath);
}

void AutoscopeWindowForm::downloadPictureButtonPressed(void)
{
    qDebug() << "downloadPictureButtonPressed";

    m_autoscopePictureWindow->updateImage(QPixmap(":/Autoscope/dossier.png"));
}

void AutoscopeWindowForm::update()
{
    QPoint mousePosition = QCursor::pos();
    QPoint displayTopLeftPosition = m_autoscopePictureWindow->pos();
    QPoint displayBottomRightPosition;
    displayBottomRightPosition.setX(displayTopLeftPosition.x()+m_autoscopePictureWindow->getGuiWidth());
    displayBottomRightPosition.setY(displayTopLeftPosition.y()+m_autoscopePictureWindow->getGuiHeight());

        qDebug() << "xy: " << mousePosition.x() << " " << mousePosition.y();

    if( (( (mousePosition.x()<displayTopLeftPosition.x()) | (mousePosition.x()>displayBottomRightPosition.x()) | (mousePosition.y()<displayTopLeftPosition.y()) | (mousePosition.y()>displayBottomRightPosition.y()) )))
    {
        qDebug() << "ko1";
        ui->displayOpacityEditor->setValue(.25);
    }else{
        qDebug() << "ok1";
        ui->displayOpacityEditor->setValue(.75);
    }

    if( (((mousePosition.x()<(m_screenWidth-m_width)) | (mousePosition.y()<(m_screenHeight-m_height)))))
    {
        qDebug() << "ko2";
        this->setWindowOpacity(.5);
    }else{
        qDebug() << "ok2";
        this->setWindowOpacity(1);
    }
}
