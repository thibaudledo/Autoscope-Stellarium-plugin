#ifndef AUTOSCOPEPICTUREWINDOWFORM_HPP
#define AUTOSCOPEPICTUREWINDOWFORM_HPP

#include <QWidget>

#include "StelDialog.hpp"

#include "Autoscope.hpp"
#include "ui_AutoscopePictureWindowForm.h"

class Autoscope;

/*!
 * \file AutoscopePictureWindowForm.hpp
 * \brief Header file including the picture display window definition
 * \author thibaud-ledoledec
 */

/*!
 * \class AutoscopePictureWindowForm
 * \brief This class is use to build a picture display interface to show to the user the last taken picture
 */
class AutoscopePictureWindowForm : public StelDialog
{
    Q_OBJECT

public:
    /*!
     * \brief Builder of the AutoscopePictureWindowForm class
     */
    AutoscopePictureWindowForm();

    /*!
     * \brief Destroyer of the AutoscopePictureWindowForm class
     */
    ~AutoscopePictureWindowForm();

    /*!
     * \brief Method used to update calculation and displayed components
     */
    void update();

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
     * \brief Setter used to set the horizontal gui position
     * \param The horizontal gui position in pixel
     */
    void setGuiHorizontalPosition(int);

    /*!
     * \brief Setter used to set the vertical gui position
     * \param The vertical gui position in pixel
     */
    void setGuiVerticalPosition(int);

    /*!
     * \brief Getter used to retreive the gui width
     * \return The gui width
     */
    int getGuiWidth(void);

    /*!
     * \brief Getter used to retreive the gui height
     * \return The gui height
     */
    int getGuiHeight(void);

    /*!
     * \brief Setter used to set the gui size in percent of the screen
     * \param The gui size in percent of the screen
     */
    void setGuiSize(int);

    /*!
     * \brief Method used to update the size of the gui
     */
    void updateGuiSize(void);

    /*!
     * \brief Setter used to set the gui opacity
     * \param the gui opacity
     */
    void setGuiOpacity(double);

    /*!
     * \brief Method used to update the gui position
     */
    void updateGuiPosition(void);

    /*!
     * \brief Method used to update the image of the gui
     * \param image
     */
    void updateImage(QPixmap image);

    /*!
     * \brief Setter used to initialize an instance of AutoscopeWindowForm class
     * \param autoscopeWindow an instance of AutoscopeWindowForm class
     */
    void setAutoscopeWindow(AutoscopeWindowForm* autoscopeWindow){m_autoscopeWindow = autoscopeWindow;}

protected:

    /*!
     * \brief This method is inherited form the StelDialog class and is use to create the content of the dialog box
     * \see StelDialog
     */
    void createDialogContent();

private:

    Ui_AutoscopePictureWindowForm* ui; /*!< An instance of the Ui_AutoscopePictureWindowForm class */

    Autoscope* m_autoscope; /*!< An instance of the Autoscope class */
    AutoscopeWindowForm* m_autoscopeWindow; /*!< An instance of the AutoscopeWindowForm class */

    int m_width = 192;  /*!< The width of the dialog box */
    int m_height = 108; /*!< The height of the dialog box */

    int m_screenWidth;  /*!< The width of the screen */
    int m_screenHeight; /*!< The height of the screen */

    int m_guiHorizontalPosition;    /*!< The horizontal position of the dialog box */
    int m_guiVerticalPosition;      /*!< The vertical position of the dialog box */

public slots:

    /*!
     * \brief Inherited from the StelDialog class
     * \see StelDialog
     */
    void retranslate();
};

#endif // AUTOSCOPEPICTUREWINDOWFORM_HPP
