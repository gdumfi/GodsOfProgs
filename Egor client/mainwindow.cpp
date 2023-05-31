#include <QWidget>  // Подключение заголовочного файла "QWidget"
#include <QDebug>  // Подключение заголовочного файла "QDebug"
#include <QMessageBox>  // Подключение заголовочного файла "QMessageBox"

#include "singletonclient.h"  // Подключение пользовательского заголовочного файла "singletonclient.h"
#include "mainwindow.h"  // Подключение пользовательского заголовочного файла "mainwindow.h"
#include "ui_mainwindow.h"  // Подключение пользовательского заголовочного файла "ui_mainwindow.h"

/**
 * \brief Конструктор класса MainWindow
 * \param parent Родительский виджет
 */
MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);  // Настройка пользовательского интерфейса, связанного с этим главным окном
    //SingletonClient::getInstance()->slot_connected();  // Вызов метода для установления соединения с сервером
}

/**
 * \brief Деструктор класса MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;  // Освобождение памяти, занятой пользовательским интерфейсом
    delete RegistrationWindow;  // Освобождение памяти, занятой объектом окна регистрации
    delete MathematicalTasksWindow;  // Освобождение памяти, занятой объектом окна математических задач
}

/**
 * \brief Обработчик нажатия на кнопку "Войти"
 */
void MainWindow::on_pushButton_Log_clicked()
{
    QString query = "auth&" + ui->lineEdit_Login->text() + "&" + ui->lineEdit_Password->text();  // Формирование запроса аутентификации

    SingletonClient::getInstance()->slot_send_to_server(query);  // Отправка запроса аутентификации на сервер
    QString str = SingletonClient::getInstance()->slot_ready_read();  // Получение ответа от сервера
    qDebug() << str;  // Вывод ответа в отладочную консоль

    if (str == "auth&+"){  // Проверка ответа от сервера
        MathematicalTasks *MathematicalTasksWindow = new MathematicalTasks;  // Создание объекта окна математических задач
        MathematicalTasksWindow->show();  // Отображение окна математических задач
    }
    else{
        QMessageBox::information(this, "Ошибка входа", "Пароль или логин неверны");  // Вывод информационного сообщения об ошибке входа
    }
}

/**
 * \brief Обработчик нажатия на кнопку "Регистрация"
 */
void MainWindow::on_pushButton_Reg_clicked()
{
    this->hide();  // Скрытие текущего главного окна
    Registration *RegistrationWindow = new Registration;  // Создание объекта окна регистрации
    RegistrationWindow->show();  // Отображение окна регистрации
}

/**
 * \brief Обработчик нажатия на кнопку "Выход"
 */
void MainWindow::on_pushButton_Exit_clicked()
{
    QString query;
    query = "exit";  // Формирование запроса выхода
    SingletonClient::getInstance()->slot_send_to_server(query);  // Отправка запроса выхода на сервер
    close();  // Закрытие главного окна
}
