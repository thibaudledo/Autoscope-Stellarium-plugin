#ifndef AUTOSCOPEPICTUREWINDOWFORM_HPP
#define AUTOSCOPEPICTUREWINDOWFORM_HPP

#include <QWidget>

#include "Autoscope.hpp"

class Autoscope;

namespace Ui {
class AutoscopePictureWindowForm;
}

class AutoscopePictureWindowForm : public QWidget
{
    Q_OBJECT

public:
    explicit AutoscopePictureWindowForm(QWidget *parent = nullptr, Autoscope* autoscope = nullptr, AutoscopeWindowForm* autoscopeWindow = nullptr, int screenWidth = 1920, int screenHeight = 1080);
    ~AutoscopePictureWindowForm();

    int getGuiHorizontalPosition(void);
    int getGuiVerticalPosition(void);

    void setGuiHorizontalPosition(int);
    void setGuiVerticalPosition(int);

    int getGuiWidth(void);
    int getGuiHeight(void);

    void setGuiSize(int);

    void setGuiOpacity(double);

    void updateGuiPosition(void);

    void updateImage(QPixmap image);

private:
    Ui::AutoscopePictureWindowForm *ui;

    Autoscope* m_autoscope;
    AutoscopeWindowForm* m_autoscopeWindow;

    int m_width = 192;
    int m_height = 108;

    int m_screenWidth;
    int m_screenHeight;

    int m_guiHorizontalPosition;
    int m_guiVerticalPosition;

    int m_guiUserHorizontalPosition;
    int m_guiUserVerticalPosition;
};

#endif // AUTOSCOPEPICTUREWINDOWFORM_HPP
