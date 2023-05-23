#include "mathematicaltasks.h"
#include "ui_mathematicaltasks.h"
#include "singletonclient.h"
#include <random>
int random1_1 = std::rand();
int random1_2 = std::rand();
int random2_1= std::rand();
int random2_2 = std::rand();
int random3_1 = std::rand();
int random3_2 = std::rand();
int random4_1 = std::rand();
int random4_2 = std::rand();
QString a1;
QString a2;
QString a3;
QString a4;

QString condition_1 = "Сложи " + QString::number(random1_1) + " с " + QString::number(random1_2);
QString condition_2 = "Сложи " + QString::number(random2_1) + " с " + QString::number(random2_2);
QString condition_3 = "Сложи " + QString::number(random3_1) + " с " + QString::number(random3_2);
QString condition_4 = "Сложи " + QString::number(random4_1) + " с " + QString::number(random4_2);

QStringList params; //это будет список правильных ответов, с которыми будут сравниваться ответы ользователей

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
    QString query;
    query.clear();
    query = "task&" + QString::number(random1_1) + "||" + QString::number(random1_2) + "&" +
            QString::number(random2_1) + "||" + QString::number(random2_2) + "&" +
            QString::number(random3_1) + "||" + QString::number(random3_2) + "&" +
            QString::number(random4_1) + "||" + QString::number(random4_2);
    SingletonClient::getInstance()->slot_send_to_server(query);
    QString str = SingletonClient::getInstance()->slot_ready_read();
    params = str.split('&');//заполнение данного списка с ответами
    params.pop_front();
    qDebug()<<params;
    qDebug()<<"я прошел строку";
    ui->label_Task->setText(condition_1);

}

MathematicalTasks::~MathematicalTasks()
{
    delete ui;
    delete stat;
}

void MathematicalTasks::on_pushButton_Exit_clicked()//дописать удаление сокета из БД

{

    QString query;
    query = "exit";
    SingletonClient::getInstance()->slot_send_to_server(query);
    close();
}

void MathematicalTasks::on_pushButton_Next_clicked()

{
    this->resolve_stat();
    int NumTask = ui->label_NextTask->text().toInt();

    int NextNumTask = NumTask + 1;
    if(NextNumTask > 4) NextNumTask = 1;

    switch (NextNumTask) {
        case 1: {
            QString condition_1 = "Сложи " + QString::number(random1_1) + " с " + QString::number(random1_2);
            ui->label_Task->setText(condition_1);
            ui->label_NextTask->setText(QString::number(NextNumTask));
            ui->lineEdit_Answer->setText("");
            break;
        }
        case 2: {
            QString condition_2 = "Сложи " + QString::number(random2_1) + " с " + QString::number(random2_2);
            ui->label_Task->setText(condition_2);
            ui->label_NextTask->setText(QString::number(NextNumTask));
            ui->lineEdit_Answer->setText("");
            break;
        }
        case 3: {
            QString condition_3 = "Сложи " + QString::number(random3_1) + " с " + QString::number(random3_2);
            ui->label_Task->setText(condition_3);
            ui->label_NextTask->setText(QString::number(NextNumTask));
            ui->lineEdit_Answer->setText("");
            break;
        }
        case 4: {
            QString condition_4 = "Сложи " + QString::number(random4_1) + " с " + QString::number(random4_2);
            ui->label_Task->setText(condition_4);
            ui->label_NextTask->setText(QString::number(NextNumTask));
            ui->lineEdit_Answer->setText("");
            break;
        }
        default:
            break;
    }
}
void MathematicalTasks::on_pushButton_Back_clicked()
{
    this->resolve_stat();
    int NumTask = ui->label_NextTask->text().toInt();

    int BackNumTask = NumTask - 1;
    if(BackNumTask < 1) BackNumTask = 4;
    switch (BackNumTask) {
        case 1: {
            QString condition_1 = "Сложи " + QString::number(random1_1) + " с " + QString::number(random1_2);
            ui->label_Task->setText(condition_1);
            ui->label_NextTask->setText(QString::number(BackNumTask));
            ui->lineEdit_Answer->setText("");
            break;
        }
        case 2: {
            QString condition_2 = "Сложи " + QString::number(random2_1) + " с " + QString::number(random2_2);
            ui->label_Task->setText(condition_2);
            ui->label_NextTask->setText(QString::number(BackNumTask));
            ui->lineEdit_Answer->setText("");
            break;
        }
        case 3: {
            QString condition_3 = "Сложи " + QString::number(random3_1) + " с " + QString::number(random3_2);
            ui->label_Task->setText(condition_3);
            ui->label_NextTask->setText(QString::number(BackNumTask));
            ui->lineEdit_Answer->setText("");
            break;
        }
        case 4: {
            QString condition_4 = "Сложи " + QString::number(random4_1) + " с " + QString::number(random4_2);
            ui->label_Task->setText(condition_4);
            ui->label_NextTask->setText(QString::number(BackNumTask));
            ui->lineEdit_Answer->setText("");
            break;
        }
        default:
            break;
    }

}

void MathematicalTasks::on_pushButton_Stat_clicked()
{
    //this->resolve_stat();
    stat->show();
}

void MathematicalTasks::resolve_stat()//дописать, чтобы + и - добавлялись в окно статики, которые выводится при нажатии на соответсвующую кнопку
{

    int NumTask = ui->label_NextTask->text().toInt();
    QString Answer = ui->lineEdit_Answer->text();
    switch (NumTask) {
        case 1: {
            if (Answer==params[0]){
                qDebug()<<"Правильно решили 1 номер";
                QString query;
                query.clear();
                query = QString("resolve&1&+");
                emit signal1("+");
                a1="+";
                SingletonClient::getInstance()->slot_send_to_server(query);

                //написать отпраку на сервер +
            }else{
                qDebug()<<"Не правильно решили 1 номер";
                QString query;
                query.clear();
                query = QString("resolve&1&-");
                qDebug()<<a1;
                if (a1!="+"){
                    emit signal1("-");
                }

                SingletonClient::getInstance()->slot_send_to_server(query);
                //написать отпраку на сервер -
            }
        }
        case 2: {
            if (Answer==params[1]){
                qDebug()<<"Правильно решили 2 номер";
                QString query;
                query.clear();
                query = QString("resolve&2&+");
                emit signal2("+");
                a2="+";
                SingletonClient::getInstance()->slot_send_to_server(query);
                //написать отпраку на сервер +
            }else{
                qDebug()<<"Не правильно решили 2 номер";
                QString query;
                query.clear();
                query = QString("resolve&2&-");
                qDebug()<<a2;
                if (a2!="+"){
                    emit signal2("-");
                }

                SingletonClient::getInstance()->slot_send_to_server(query);
                //написать отпраку на сервер -
            }
        }
        case 3: {
            if (Answer==params[2]){
                qDebug()<<"Правильно решили 3 номер";
                QString query;
                query.clear();
                query = QString("resolve&3&+");
                emit signal3("+");
                a3="+";
                SingletonClient::getInstance()->slot_send_to_server(query);
                //написать отпраку на сервер +
            }else{
                qDebug()<<"Не правильно решили 3 номер";
                QString query;
                query.clear();
                query = QString("resolve&3&-");
                qDebug()<<a3;
                if (a3!="+"){
                    emit signal3("-");
                }

                SingletonClient::getInstance()->slot_send_to_server(query);
                //написать отпраку на сервер -
            }
        }
        case 4: {
            if (Answer==params[3]){
                qDebug()<<"Правильно решили 4 номер";
                QString query;
                query.clear();
                query = QString("resolve&4&+");
                emit signal4("+");
                a4="+";
                SingletonClient::getInstance()->slot_send_to_server(query);
                //написать отпраку на сервер +
            }else{
                qDebug()<<"Не правильно решили 4 номер";
                QString query;
                query.clear();
                query = QString("resolve&4&-");
                qDebug()<<a4;
                if (a4!="+"){
                    emit signal4("-");
                }
                SingletonClient::getInstance()->slot_send_to_server(query);
                //написать отпраку на сервер -
            }
        }
        default:
            break;
    }

}


