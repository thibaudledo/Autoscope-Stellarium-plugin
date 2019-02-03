#ifndef AUTOSCOPEWINDOWFORM_H
#define AUTOSCOPEWINDOWFORM_H

#include <QWidget>

#include "StelDialog.hpp"

#include "Autoscope.hpp"
#include "ui_AutoscopeWindowForm.h"
#include "AutoscopePictureWindowForm.hpp"

class Autoscope;
class AutoscopePictureWindowForm;

/*!
 * \file AutoscopeWindowForm.hpp
 * \brief Header file including configuration window definition
 * \author thibaud-ledoledec
 */

/*!
 * \class AutoscopeWindowForm
 * \brief This class is use to build a configuration interface between the user and the plugin
 */
class AutoscopeWindowForm : public StelDialog
{
    Q_OBJECT

public:
    /*!
     * \brief Builder of the AutoscopeWindowForm class
     */
    AutoscopeWindowForm();

    /*!
     * \brief Destroyer of the AutoscopeWindowForm class
     */
    ~AutoscopeWindowForm();

    /*!
     * \brief Method used to update calculation and displayed components
     */
    void update();

    /*!
     * \brief Setter used to initialize an instance of AutoscopePictureWindowForm class
     * \param autoscopePictureWindow An instance of AutoscopePictureWindowForm class
     */
    void setAutoscopePictureWindow(AutoscopePictureWindowForm* autoscopePictureWindow){m_autoscopePictureWindow = autoscopePictureWindow;}

    /*!
     * \brief Getter used to retreive the horizontal gui position
     * \return The horizontal gui position
     */
    int getGuiHorizontalPosition(void);

    /*!
     * \brief Getter used to retreive the vertical gui position
     * \return The vertical gui position
     */
    int getGuiVerticalPosition(void);

    /*!
     * \brief Getter used to retreive the value of the display size editor
     * \return The value of the display size editor
     */
    int getScreenSizePercent(void);

    /*!
     * \brief Method used to update the gui size
     */
    void updateGuiSize(void);

    /*!
     * \brief Method used to update the gui position
     */
    void updateGuiPosition(void);

    /*!
     * \brief Method used to toggle the visibility of the picture display
     */
    void toggleDisplay(void);

    /*!
     * \brief Method used to update the IP messenger text
     * \param the text to put in the messenger
     */
    void updateIpMessengerText(QString);

protected:

    /*!
     * \brief This method is inherited form the StelDialog class and it's use to create the content of the dialog box
     * \see StelDialog
     */
    void createDialogContent();

private:

    Ui_AutoscopeWindowForm* ui; /*!< An instance of the Ui_AutoscopeWindowForm class */

    int m_width = 600;  /*!< The width of the dialog box */
    int m_height = 300; /*!< The height of the dialog box */

    int m_screenWidth;  /*!< The width of the screen */
    int m_screenHeight; /*!< The height of the screen */

    int m_guiHorizontalPosition;    /*!< The gui horizontal position */
    int m_guiVerticalPosition;      /*!< The gui vertical position */

    int screenSizePercent;  /*!< The size of the dialog box in percent of the screen */

    bool pictureWindowIsVisible = false;    /*!< Flag which represent the visibility of the picture display window */

    /*!
     * \brief An instance of Autoscope class
     * \see Autoscope
     */
    Autoscope* m_autoscope;

    /*!
     * \brief An instance of AutoscopePictureWindowForm class
     * \see AutoscopePictureWindowForm
     */
    AutoscopePictureWindowForm* m_autoscopePictureWindow;

    QString picturedirectoryPath = "";  /*!< The path where to put downloaded picture */

    /*!
     * \brief Method used to update max and min value of the position slider
     */
    void updateMaxMinSlider(void);

public slots:

    /*!
     * \brief Inherited from the StelDialog class
     * \see StelDialog
     */
    void retranslate();

    /*!
     * \brief Start initialization of the telescope
     */
    void startButtonPressed(void);

    /*!
     * \brief Start tracking the selected object
     */
    void trackButtonPressed(void);

    /*!
     * \brief Stop tracking the tracked object
     */
    void untrackButtonPressed(void);

    /*!
     * \brief Send a command to the telescope to take a picture
     */
    void takePictureButtonPressed(void);

    /*!
     * \brief Toggle the visibility of the picture display
     */
    void toggleDisplayButtonPressed(void);

private slots:

    /*!
     * \brief Move to an azimuth and an altitude
     */
    void moveToButtonPressed(void);

    /*!
     * \brief Update azimuth value
     */
    void azimuthChanged(double);

    /*!
     * \brief Update altitude value
     */
    void altitudeChanged(double);

    /*!
     * \brief Update searched object
     */
    void searchObjectChanged(QString);

    /*!
     * \brief Move to the searched object and track it
     */
    void searchButtonPressed(void);

    /*!
     * \brief Update zoom value
     */
    void zoomChanged(int);

    /*!
     * \brief Update exposure time
     */
    void exposureTimeChanged(double);

    /*!
     * \brief Update the number of picture taken at each time
     */
    void numberOfPictureChanged(int);

    /*!
     * \brief Update the size value of the picture display
     */
    void displaySizeChanged(int);

    /*!
     * \brief Update the horizontal position value of the picture display
     */
    void horizontalDisplayPositionChanged(int);

    /*!
     * \brief Update the vertical position value of the picture display
     */
    void verticalDisplayPositionChanged(int);

    /*!
     * \brief Update the opacity value of the picture display
     */
    void displayOpacityChanged(int);

    /*!
     * \brief Update the path to put picture into
     */
    void outputPictureDirectoryChanged(void);

    /*!
     * \brief Show directory browser to select the directory to put picture into
     */
    void outputPictureDirectoryButtonPressed(void);

    /*!
     * \brief Download the last picture taken
     */
    void downloadPictureButtonPressed(void);

    /*!
     * \brief Update the IP address of the telescope
     */
    void ipAddressChanged(QString);

    /*!
     * \brief Update the IP port of the telescope
     */
    void ipPortChanged(int);

    /*!
     * \brief Connect to the IP address and port
     */
    void connectionButtonPressed(void);

    /*!
     * \brief Disconnect form the telescope
     */
    void deconnectionButtonPressed(void);
};

#endif // AUTOSCOPEWINDOWFORM_H
