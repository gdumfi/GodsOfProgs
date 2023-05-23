#include <QWidget>
#include <QDebug>

#include "registration.h"
#include "ui_registration.h"
#include "singletonclient.h"

Registration::Registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
}

Registration::~Registration()
{
    delete ui;
    delete MathematicalTasksWindow;
}

void Registration::on_pushButton_Exit_clicked()
{

    QString query;
    query = "exit";
    SingletonClient::getInstance()->slot_send_to_server(query);
    close();
}

void Registration::on_pushButton_Log_clicked()
{
    QString query = "reg&"+ui->lineEdit_Login->text()+"&"+ui->lineEdit_Email->text()+"&"+ui->lineEdit_Password->text();

    SingletonClient::getInstance()->slot_send_to_server(query);
    QString str = SingletonClient::getInstance()->slot_ready_read();
    qDebug()<<str;
    if (str == "reg&+"){
        this->hide();
        MathematicalTasks *MathematicalTasksWindow = new MathematicalTasks;
        MathematicalTasksWindow->show();
    }

}
