#ifndef AUTOSCOPEPICTUREWINDOWFORM_HPP
#define AUTOSCOPEPICTUREWINDOWFORM_HPP

#include <QWidget>

#include "StelDialog.hpp"

#include "Autoscope.hpp"
#include "ui_AutoscopePictureWindowForm.h"
//#include "AutoscopeWindowForm.hpp"

class Autoscope;
/*
namespace Ui {
class AutoscopePictureWindowForm;
}*/

class AutoscopePictureWindowForm : public StelDialog
{
    Q_OBJECT

public:
    AutoscopePictureWindowForm();
    ~AutoscopePictureWindowForm();

    void update();

    int getGuiHorizontalPosition(void);
    int getGuiVerticalPosition(void);

    void setGuiHorizontalPosition(int);
    void setGuiVerticalPosition(int);

    int getGuiWidth(void);
    int getGuiHeight(void);

    void setGuiSize(int);

    void updateGuiSize(void);

    void setGuiOpacity(double);

    void updateGuiPosition(void);

    void updateImage(QPixmap image);

    void setAutoscopeWindow(AutoscopeWindowForm* autoscopeWindow){m_autoscopeWindow = autoscopeWindow;}

protected:
    void createDialogContent();

private:
    Ui_AutoscopePictureWindowForm* ui;

    Autoscope* m_autoscope;
    AutoscopeWindowForm* m_autoscopeWindow;

    int m_width = 192;
    int m_height = 108;

    int m_screenWidth;
    int m_screenHeight;

    int m_guiHorizontalPosition;
    int m_guiVerticalPosition;

    int m_guiUserHorizontalPosition = 0;
    int m_guiUserVerticalPosition = 0;

public slots:
    void retranslate();
};

#endif // AUTOSCOPEPICTUREWINDOWFORM_HPP
