#include "mathematicaltasks.h"
#include "ui_mathematicaltasks.h"
#include "singletonclient.h"
#include <random>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>


QString generateRandomValues(int n) {

    QString values;
    for (int i = 0; i < n; ++i) {
        int value = rand() % 2 == 0; // Генерация случайного значения (true или false)
        values.append(QString::number(value)+";");
    }
    values.chop(1);
    return values;
}




/*QString condition_1 = "Сложи " + QString::number(random1_1) + " с " + QString::number(random1_2);
QString condition_2 = "Сложи " + QString::number(random2_1) + " с " + QString::number(random2_2);
QString condition_3 = "Сложи " + QString::number(random3_1) + " с " + QString::number(random3_2);
QString condition_4 = "Сложи " + QString::number(random4_1) + " с " + QString::number(random4_2);*/



/**
 * @brief Конструктор класса MathematicalTasks
 * @param parent Указатель на родительский виджет
 */
MathematicalTasks::MathematicalTasks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MathematicalTasks)
{
    ui->setupUi(this);
    stat = new Stat;
    connect(this, &MathematicalTasks::signal1, stat, &Stat::slot1);
    connect(this, &MathematicalTasks::signal2, stat, &Stat::slot2);
    connect(this, &MathematicalTasks::signal3, stat, &Stat::slot3);
    connect(this, &MathematicalTasks::signal4, stat, &Stat::slot4);

    srand(static_cast<unsigned>(time(0)));
    for(int i=0;i<4;i++)
        random.push_back(generateRandomValues(8));

    getanswers();

    ui->label_Task->setText(gettask(1));
}


void MathematicalTasks::getanswers()
{
    QString query;
    query.clear();
    query = "task&" + random[0] + "&" +
            random[1] + "&" +
            random[2] + "&" +
            random[3];
    SingletonClient::getInstance()->slot_send_to_server(query);
    QString str = SingletonClient::getInstance()->slot_ready_read();
    params = str.split('&'); // Заполнение данного списка с ответами
    params.pop_front();
    qDebug() << params;
    qDebug() << "я прошел строку";
}


/**
 * @brief Деструктор класса MathematicalTasks
 */
MathematicalTasks::~MathematicalTasks()
{
    delete ui;
    delete stat;
}

void MathematicalTasks::on_pushButton_Exit_clicked()
{
    QString query;
    query = "exit";
    SingletonClient::getInstance()->slot_send_to_server(query);
    close();
}

QString MathematicalTasks::gettask(int num)
{
    switch (num) {
    case 1: {
        return "Найди СДНФ по вектору значений функции: " + random[0];
        break;
    }
    case 2: {
       return "Найди СКНФ по вектору значений функции: " + random[1];
        break;
    }
    case 3: {
        return "Найди МДНФ по вектору значений функции: " + random[2];
        break;
    }
    case 4: {
        return "Найди МКНФ по вектору значений функции: " + random[3];
        break;
    }
    default:
        break;
    }
}

void MathematicalTasks::on_pushButton_Next_clicked()
{
    int NumTask = ui->label_NextTask->text().toInt();
    this->resolve_stat();
    int NextNumTask = NumTask + 1;
    if (NextNumTask > 4)
        NextNumTask = 1;


    ui->label_Task->setText(gettask(NextNumTask));
    ui->label_NextTask->setText(QString::number(NextNumTask));
    ui->lineEdit_Answer->setText("");
}

void MathematicalTasks::on_pushButton_Back_clicked()
{
    int NumTask = ui->label_NextTask->text().toInt();
    this->resolve_stat();
    int BackNumTask = NumTask - 1;
    if (BackNumTask < 1)
    {
        BackNumTask = 4;
    }
    ui->label_Task->setText(gettask(BackNumTask));
    ui->label_NextTask->setText(QString::number(BackNumTask));
    ui->lineEdit_Answer->setText("");
}

void MathematicalTasks::on_pushButton_Stat_clicked()
{
    stat->show();
}

void MathematicalTasks::resolve_stat()
{
    QString a1;
    QString a2;
    QString a3;
    QString a4;

    int NumTask = ui->label_NextTask->text().toInt();
    QString Answer = ui->lineEdit_Answer->text();
    switch (NumTask) {
        case 1: {
            if (Answer == params[0]) {
                qDebug() << "Правильно решили 1 номер";
                QString query;
                query.clear();
                query = QString("resolve&1&+");
                emit signal1("+");
                a1 = "+";
                SingletonClient::getInstance()->slot_send_to_server(query);
            } else {
                qDebug() << "Не правильно решили 1 номер";
                QString query;
                query.clear();
                query = QString("resolve&1&-");
                qDebug() << a1;
                if (a1 != "+") {
                    emit signal1("-");
                }
                SingletonClient::getInstance()->slot_send_to_server(query);
            }
            break;
        }
        case 2: {
            if (Answer == params[1]) {
                qDebug() << "Правильно решили 2 номер";
                QString query;
                query.clear();
                query = QString("resolve&2&+");
                emit signal2("+");
                a2 = "+";
                SingletonClient::getInstance()->slot_send_to_server(query);
            } else {
                qDebug() << "Не правильно решили 2 номер";
                QString query;
                query.clear();
                query = QString("resolve&2&-");
                qDebug() << a2;
                if (a2 != "+") {
                    emit signal2("-");
                }
                SingletonClient::getInstance()->slot_send_to_server(query);
            }
            break;
        }
        case 3: {
            if (Answer == params[2]) {
                qDebug() << "Правильно решили 3 номер";
                QString query;
                query.clear();
                query = QString("resolve&3&+");
                emit signal3("+");
                a3 = "+";
                SingletonClient::getInstance()->slot_send_to_server(query);
            } else {
                qDebug() << "Не правильно решили 3 номер";
                QString query;
                query.clear();
                query = QString("resolve&3&-");
                qDebug() << a3;
                if (a3 != "+") {
                    emit signal3("-");
                }
                SingletonClient::getInstance()->slot_send_to_server(query);
            }
            break;
        }
        case 4: {
            if (Answer == params[3]) {
                qDebug() << "Правильно решили 4 номер";
                QString query;
                query.clear();
                query = QString("resolve&4&+");
                emit signal4("+");
                a4 = "+";
                SingletonClient::getInstance()->slot_send_to_server(query);
            } else {
                qDebug() << "Не правильно решили 4 номер";
                QString query;
                query.clear();
                query = QString("resolve&4&-");
                qDebug() << a4;
                if (a4 != "+") {
                    emit signal4("-");
                }
                SingletonClient::getInstance()->slot_send_to_server(query);
            }
            break;
        }
        default:
            break;
    }
}
