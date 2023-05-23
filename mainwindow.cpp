#include <QWidget>
#include <QDebug>
#include <QMessageBox>

#include "singletonclient.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //SingletonClient::getInstance()->slot_connected();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete RegistrationWindow;
    delete MathematicalTasksWindow;
}

void MainWindow::on_pushButton_Log_clicked()
{
    QString query = "auth&" + ui->lineEdit_Login->text() + "&" + ui->lineEdit_Password->text();

    SingletonClient::getInstance()->slot_send_to_server(query);
    QString str = SingletonClient::getInstance()->slot_ready_read();
    qDebug() << str;

    if (str == "auth&+"){
        MathematicalTasks *MathematicalTasksWindow = new MathematicalTasks;
        MathematicalTasksWindow->show();
    }
    else{
        QMessageBox::information(this, "Ошибка входа", "Пароль или логин неверны");
    }
}

void MainWindow::on_pushButton_Reg_clicked()
{
    Registration *RegistrationWindow = new Registration;
    RegistrationWindow->show();
}


void MainWindow::on_pushButton_Exit_clicked()
{

    QString query;
    query = "exit";
    SingletonClient::getInstance()->slot_send_to_server(query);
    close();
}

