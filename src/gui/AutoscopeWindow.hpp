#ifndef AUTOSCOPEWINDOW_HPP
#define AUTOSCOPEWINDOW_HPP

#include <QWidget>

namespace Ui {
class AutoscopeWindow;
}

class AutoscopeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AutoscopeWindow(QWidget *parent = nullptr);
    ~AutoscopeWindow();

private:
    Ui::AutoscopeWindow *ui;
};

#endif // AUTOSCOPEWINDOW_HPP
