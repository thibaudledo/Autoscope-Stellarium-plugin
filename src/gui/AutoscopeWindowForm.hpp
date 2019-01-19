#ifndef AUTOSCOPEWINDOWFORM_H
#define AUTOSCOPEWINDOWFORM_H

#include <QWidget>

#include "Autoscope.hpp"

class Autoscope;

namespace Ui {
class AutoscopeWindowForm;
}

class AutoscopeWindowForm : public QWidget
{
    Q_OBJECT

public:
    explicit AutoscopeWindowForm(QWidget *parent = nullptr, Autoscope* autoscope = nullptr);
    ~AutoscopeWindowForm();

    int getGuiHorizontalPosition(void);
    int getGuiVerticalPosition(void);

private:

    Ui::AutoscopeWindowForm *ui;

    int m_width = 600;
    int m_height = 300;

    int m_guiHorizontalPosition;
    int m_guiVerticalPosition;

    Autoscope* m_autoscope;

    QString picturedirectoryPath = "";

public slots:
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
