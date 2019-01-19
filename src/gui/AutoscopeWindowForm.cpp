#include "AutoscopeWindowForm.hpp"
#include "ui_AutoscopeWindowForm.h"
#include <QDesktopWidget>
#include <QDebug>

#include <QFileDialog>

class Autoscope;

AutoscopeWindowForm::AutoscopeWindowForm(QWidget *parent, Autoscope* autoscope) :
    QWidget(parent),
    ui(new Ui::AutoscopeWindowForm)
{
    m_autoscope = autoscope;

    resize(m_width, m_height);
    QDesktopWidget screen;
    QRect screenSize = screen.screenGeometry();

    m_guiHorizontalPosition = screenSize.width()- m_width;
    m_guiVerticalPosition = screenSize.height()- m_height;

    move(m_guiHorizontalPosition, m_guiVerticalPosition);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    ui->setupUi(this);

    ui->verticalDisplayPositionEditor->setMaximum(screenSize.height());
    ui->verticalDisplayPositionEditor->setValue(screenSize.height() - m_height);

    ui->horizontalDisplayPositionEditor->setMaximum(screenSize.width());
    ui->horizontalDisplayPositionEditor->setValue(screenSize.width()- m_width);

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

void AutoscopeWindowForm::displaySizeChanged(int i)
{
    qDebug() << "displaySizeChanged";
}

void AutoscopeWindowForm::horizontalDisplayPositionChanged(int i)
{
    qDebug() << "horizontalDisplayPositionChanged";
}

void AutoscopeWindowForm::verticalDisplayPositionChanged(int i)
{
    qDebug() << "verticalDisplayPositionChanged";
}

void AutoscopeWindowForm::displayOpacityChanged(double d)
{
    qDebug() << "displayOpacityChanged";
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
}

