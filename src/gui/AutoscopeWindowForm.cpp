#include "AutoscopeWindowForm.hpp"
#include "ui_AutoscopeWindowForm.h"

#include <QDebug>

#include <QFileDialog>
#include "AutoscopePictureWindowForm.hpp"

#include "StelModule.hpp"
#include "StelModuleMgr.hpp"

#include "AutoscopeFtpDialog.hpp"

class Autoscope;

AutoscopeWindowForm::AutoscopeWindowForm()
    : StelDialog("Autoscope"),
      m_autoscope(Q_NULLPTR)
{
    ui = new Ui_AutoscopeWindowForm();
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
    qDebug() << "createDialogContent";
    m_autoscope = GETSTELMODULE(Autoscope);
    m_autoscopePictureWindow = m_autoscope->getAutoscopePictureWindow();
    m_parser = m_autoscope->getCommandParser();

    ui->setupUi(dialog);

    m_screenWidth = m_autoscope->getScreenWidth();
    m_screenHeight = m_autoscope->getScreenHeight();

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
    //connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this, SLOT(zoomChanged(int)));
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startButtonPressed(void)));
    connect(ui->trackButton, SIGNAL(clicked()), this, SLOT(trackButtonPressed(void)));
    connect(ui->untrackButton, SIGNAL(clicked()), this, SLOT(untrackButtonPressed(void)));
    connect(ui->takePictureButton, SIGNAL(clicked()), this, SLOT(takePictureButtonPressed(void)));
    connect(ui->toggleDisplayButton, SIGNAL(clicked()), this, SLOT(toggleDisplayButtonPressed(void)));
    connect(ui->exposureTimeEditor, SIGNAL(valueChanged(double)), this, SLOT(exposureTimeChanged(double)));
    connect(ui->numberPictureEditor, SIGNAL(valueChanged(int)), this, SLOT(numberOfPictureChanged(int)));
    connect(ui->horizontalDisplayPositionSlider, SIGNAL(valueChanged(int)), this, SLOT(horizontalDisplayPositionChanged(int)));
    connect(ui->verticalDisplayPositionSlider, SIGNAL(valueChanged(int)), this, SLOT(verticalDisplayPositionChanged(int)));
    connect(ui->picturePathEditor, SIGNAL(returnPressed()), this, SLOT(outputPictureDirectoryChanged(void)));
    connect(ui->picurePathButton, SIGNAL(clicked()), this, SLOT(outputPictureDirectoryButtonPressed(void)));
    connect(ui->pictureDownloadButton, SIGNAL(clicked()), this, SLOT(downloadPictureButtonPressed(void)));

    connect(ui->displaySizeEditor, SIGNAL(valueChanged(int)), this, SLOT(displaySizeChanged(int)));
    connect(ui->displaySizeSlider, SIGNAL(valueChanged(int)), this, SLOT(displaySizeChanged(int)));

    connect(ui->displayOpacityEditor, SIGNAL(valueChanged(int)), this, SLOT(displayOpacityChanged(int)));
    connect(ui->displayOpacitySlider, SIGNAL(valueChanged(int)), this, SLOT(displayOpacityChanged(int)));

    connect(ui->IpAddressEditor, SIGNAL(textChanged(QString)), this, SLOT(ipAddressChanged(QString)));
    connect(ui->IpPortEditor, SIGNAL(valueChanged(int)), this, SLOT(ipPortChanged(int)));
    connect(ui->ConnectionButton, SIGNAL(clicked()), this, SLOT(connectionButtonPressed(void)));
    connect(ui->DeconnectionButton, SIGNAL(clicked()), this, SLOT(deconnectionButtonPressed(void)));

    updateMaxMinSlider();
}

void AutoscopeWindowForm::retranslate()
{

}

void AutoscopeWindowForm::updateIpMessengerText(QString message)
{
    ui->IpMessenger->setText(message);
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
    m_autoscope->sendToServer(m_parser->initCommand());
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
    m_autoscope->sendToServer(m_parser->takePictureCommand());
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
    m_autoscope->sendToServer(m_parser->moveToCommand(ui->azimuthEditor->value(), ui->altitudeEditor->value()));
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
    m_autoscope->sendToServer(m_parser->zoomCommand(i));
}

void AutoscopeWindowForm::exposureTimeChanged(double d)
{
    qDebug() << "exposureTimeChanged";
    m_autoscope->sendToServer(m_parser->exposureTimeCommand(d));
}

void AutoscopeWindowForm::numberOfPictureChanged(int i)
{
    qDebug() << "numberOfPictureChanged";
    m_autoscope->sendToServer(m_parser->numberOfPictureCommand(i));
}

void AutoscopeWindowForm::displaySizeChanged(int percent)
{
    qDebug() << "displaySizeChanged";

    if(pictureWindowIsVisible)
    {
        m_autoscopePictureWindow->setGuiSize(percent);
        //m_autoscopePictureWindow->updateGuiPosition();
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

void AutoscopeWindowForm::displayOpacityChanged(int opacity)
{
    qDebug() << "displayOpacityChanged";
    if(pictureWindowIsVisible)
    {
        double d_opacity = opacity/100.0;
        m_autoscopePictureWindow->setGuiOpacity(d_opacity);
    }
}

void AutoscopeWindowForm::updateMaxMinSlider(void)
{
    qDebug() << "updateMaxMinSlider";
    ui->horizontalDisplayPositionSlider->setMaximum(int(m_screenWidth-(m_autoscopePictureWindow->getGuiWidth())));
    ui->verticalDisplayPositionSlider->setMaximum(int(m_screenHeight-(m_autoscopePictureWindow->getGuiHeight())));
}

void AutoscopeWindowForm::outputPictureDirectoryChanged(void)
{
    qDebug() << "outputPictureDirectoryChanged";
    m_autoscopeFtpDialog->setPathToSaveFile(ui->picturePathEditor->text());
}

void AutoscopeWindowForm::outputPictureDirectoryButtonPressed(void)
{
    qDebug() << "outputPictureDirectoryButtonPressed";
    picturedirectoryPath = QFileDialog::getExistingDirectory(nullptr);
    ui->picturePathEditor->setText(picturedirectoryPath);
    m_autoscopeFtpDialog->setPathToSaveFile(ui->picturePathEditor->text());
}

void AutoscopeWindowForm::downloadPictureButtonPressed(void)
{
    qDebug() << "downloadPictureButtonPressed";

    m_autoscopeFtpDialog->setVisible(true);
}

void AutoscopeWindowForm::ipAddressChanged(QString ipAddress)
{
    qDebug() << "ipAddressChanged";
    m_autoscope->setIpAddress(ipAddress);
}

void AutoscopeWindowForm::ipPortChanged(int port)
{
    qDebug() << "ipPortChanged";
    m_autoscope->setPort(port);
}

void AutoscopeWindowForm::connectionButtonPressed(void)
{
    qDebug() << "connectionButtonPressed";
    m_autoscope->connectToAutoscope();
}

void AutoscopeWindowForm::deconnectionButtonPressed(void)
{
    qDebug() << "deconnectionButtonPressed";
    m_autoscope->deconnectFromAutoscope();
}
