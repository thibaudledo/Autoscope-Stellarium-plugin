#ifndef AUTOSCOPEWINDOWFORM_H
#define AUTOSCOPEWINDOWFORM_H

#include <QWidget>

#include "StelDialog.hpp"

#include "Autoscope.hpp"
#include "ui_AutoscopeWindowForm.h"
#include "AutoscopePictureWindowForm.hpp"

class Autoscope;
class AutoscopePictureWindowForm;
/*
namespace Ui {
class AutoscopeWindowForm;
}*/

class AutoscopeWindowForm : public StelDialog
{
    Q_OBJECT

public:
    AutoscopeWindowForm();
    ~AutoscopeWindowForm();

    void update();

    AutoscopePictureWindowForm* getAutoscopePictureWindowForm(void){if(m_autoscopePictureWindow!=nullptr)return m_autoscopePictureWindow;}

    int getGuiHorizontalPosition(void);
    int getGuiVerticalPosition(void);

    int getScreenSizePercent(void);

    int getScreenWidth(void){return m_screenWidth;}
    int getScreenHeight(void){return m_screenHeight;}

    void updateGuiSize(void);
    void updateGuiPosition(void);

protected:
    void createDialogContent();

private:

    Ui_AutoscopeWindowForm* ui;

    int m_width = 600;
    int m_height = 300;

    int m_screenWidth;
    int m_screenHeight;

    int m_guiHorizontalPosition;
    int m_guiVerticalPosition;

    int screenSizePercent;

    bool pictureWindowIsVisible = false;

    Autoscope* m_autoscope;
    AutoscopePictureWindowForm* m_autoscopePictureWindow;

    QString picturedirectoryPath = "";

public slots:
    void retranslate();
    void startButtonPressed(void);
    void trackButtonPressed(void);
    void untrackButtonPressed(void);
    void takePictureButtonPressed(void);
    void toggleDisplayButtonPressed(void);

private slots:
    void moveToButtonPressed(void);
    void azimuthChanged(double);
    void altitudeChanged(double);
    void searchObjectChanged(QString);
    void searchButtonPressed(void);
    void zoomChanged(int);
    void exposureTimeChanged(double);
    void numberOfPictureChanged(int);
    void displaySizeChanged(int);
    void horizontalDisplayPositionChanged(int);
    void verticalDisplayPositionChanged(int);
    void displayOpacityChanged(double);
    void outputPictureDirectoryChanged(void);
    void outputPictureDirectoryButtonPressed(void);
    void downloadPictureButtonPressed(void);
};

#endif // AUTOSCOPEWINDOWFORM_H
