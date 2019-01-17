#ifndef AUTOSCOPEWINDOWFORM_H
#define AUTOSCOPEWINDOWFORM_H

#include <QWidget>

namespace Ui {
class AutoscopeWindowForm;
}

class AutoscopeWindowForm : public QWidget
{
    Q_OBJECT

public:
    explicit AutoscopeWindowForm(QWidget *parent = nullptr);
    ~AutoscopeWindowForm();

private:
    Ui::AutoscopeWindowForm *ui;
};

#endif // AUTOSCOPEWINDOWFORM_H
