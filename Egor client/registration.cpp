#include <QWidget>
#include <QDebug>

#include "registration.h"
#include "ui_registration.h"
#include "singletonclient.h"

/**
 * @brief Конструктор класса Registration.
 * @param parent Указатель на родительский виджет.
 */
Registration::Registration(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
}

/**
 * @brief Деструктор класса Registration.
 */
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
    // Создание запроса с информацией для регистрации
    QString query = "reg&" + ui->lineEdit_Login->text() + "&" + ui->lineEdit_Email->text() + "&" + ui->lineEdit_Password->text();

    // Отправка запроса на сервер
    SingletonClient::getInstance()->slot_send_to_server(query);
    QString str = SingletonClient::getInstance()->slot_ready_read();
    qDebug() << str;

    // Если регистрация прошла успешно, скрыть окно регистрации и показать окно MathematicalTasks
    if (str == "reg&+") {
        this->hide();
        MathematicalTasks *MathematicalTasksWindow = new MathematicalTasks;
        MathematicalTasksWindow->show();
    }
}
