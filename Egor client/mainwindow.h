#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "registration.h"
#include "mathematicaltasks.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_Log_clicked();

    void on_pushButton_Reg_clicked();

    void on_pushButton_Exit_clicked();

private:
    Ui::MainWindow *ui;
    Registration *RegistrationWindow;
    MathematicalTasks *MathematicalTasksWindow;
};
#endif // MAINWINDOW_H
