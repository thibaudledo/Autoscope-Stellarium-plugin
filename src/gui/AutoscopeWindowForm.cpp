#include "AutoscopeWindowForm.hpp"
#include "ui_AutoscopeWindowForm.h"
#include <QDesktopWidget>
#include <QDebug>

#include <QFileDialog>
#include "AutoscopePictureWindowForm.hpp"

#include "StelModule.hpp"
#include "StelModuleMgr.hpp"

class Autoscope;

AutoscopeWindowForm::AutoscopeWindowForm()
    : StelDialog("Autoscope"),
      m_autoscope(Q_NULLPTR)
{
    ui = new Ui_AutoscopeWindowForm();
    m_autoscopePictureWindow = new AutoscopePictureWindowForm(this);
}

AutoscopeWindowForm::~AutoscopeWindowForm()
{
    delete ui;
}

void AutoscopeWindowForm::update()
{
    if(pictureWindowIsVisible)
    {
        m_autoscopePictureWindow->updateGuiSize();
    }
}

void AutoscopeWindowForm::createDialogContent()
{
    m_autoscope = GETSTELMODULE(Autoscope);

    ui->setupUi(dialog);

    QDesktopWidget screen;
    QRect screenSize = screen.screenGeometry();

    m_screenWidth = screenSize.width();
    m_screenHeight = screenSize.height();

    m_guiHorizontalPosition = m_screenWidth - m_width;
    m_guiVerticalPosition = m_screenHeight - m_height;

    dialog->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

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
    connect(ui->horizontalDisplayPositionSlider, SIGNAL(valueChanged(int)), this, SLOT(horizontalDisplayPositionChanged(int)));
    connect(ui->verticalDisplayPositionSlider, SIGNAL(valueChanged(int)), this, SLOT(verticalDisplayPositionChanged(int)));
    connect(ui->displayOpacityEditor, SIGNAL(valueChanged(double)), this, SLOT(displayOpacityChanged(double)));
    connect(ui->picturePathEditor, SIGNAL(returnPressed()), this, SLOT(outputPictureDirectoryChanged(void)));
    connect(ui->picurePathButton, SIGNAL(clicked()), this, SLOT(outputPictureDirectoryButtonPressed(void)));
    connect(ui->pictureDownloadButton, SIGNAL(clicked()), this, SLOT(downloadPictureButtonPressed(void)));

    updateMaxMinSlider();
}

void AutoscopeWindowForm::retranslate()
{

}

void AutoscopeWindowForm::updateGuiSize(void)
{
    if((dialog->size().width()!=m_width) || (dialog->size().height()!=m_height))
    {
        dialog->resize(m_width, m_height);
    }
}

void AutoscopeWindowForm::updateGuiPosition(void)
{
    if((dialog->pos().x()!=m_guiHorizontalPosition) || (dialog->pos().y()!=m_guiVerticalPosition))
    {
        dialog->move(m_guiHorizontalPosition, m_guiVerticalPosition);
    }
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
    toggleDisplay();
}

void AutoscopeWindowForm::toggleDisplay(void)
{
    if(pictureWindowIsVisible)
    {
        m_autoscopePictureWindow->setVisible(false);
        pictureWindowIsVisible = false;
    }else{
        m_autoscopePictureWindow->setVisible(true);
        pictureWindowIsVisible = true;
        m_autoscopePictureWindow->updateGuiPosition();

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

    if(pictureWindowIsVisible)
    {
        m_autoscopePictureWindow->setGuiSize(percent);
        updateMaxMinSlider();
    }
}

void AutoscopeWindowForm::horizontalDisplayPositionChanged(int x)
{
    qDebug() << "horizontalDisplayPositionChanged";
    if(pictureWindowIsVisible)
    {
        m_autoscopePictureWindow->setGuiHorizontalPosition(x);
        updateMaxMinSlider();
    }
}

void AutoscopeWindowForm::verticalDisplayPositionChanged(int y)
{
    qDebug() << "verticalDisplayPositionChanged";
    if(pictureWindowIsVisible)
    {
        m_autoscopePictureWindow->setGuiVerticalPosition(y);
        updateMaxMinSlider();
    }
}

void AutoscopeWindowForm::displayOpacityChanged(double opacity)
{
    qDebug() << "displayOpacityChanged";
    if(pictureWindowIsVisible)
    {
        m_autoscopePictureWindow->setGuiOpacity(opacity);
    }
}

void AutoscopeWindowForm::updateMaxMinSlider(void)
{
    ui->horizontalDisplayPositionSlider->setMaximum(int(m_screenWidth));
    ui->verticalDisplayPositionSlider->setMaximum(int(m_screenHeight-(m_autoscopePictureWindow->getGuiHeight())));

    ui->horizontalDisplayPositionSlider->setMinimum(m_autoscopePictureWindow->getGuiWidth());
    ui->verticalDisplayPositionSlider->setMinimum(0);
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
