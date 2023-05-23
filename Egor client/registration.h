#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>
#include "mathematicaltasks.h"

namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = nullptr);
    ~Registration();

private slots:
    void on_pushButton_Exit_clicked();

    void on_pushButton_Log_clicked();

private:
    Ui::Registration *ui;
    MathematicalTasks *MathematicalTasksWindow;
};

#endif // REGISTRATION_H
