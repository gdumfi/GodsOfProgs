#include "stat.h"
#include "ui_stat.h"

/**
 * @brief Конструктор класса Stat.
 * @param parent Указатель на родительский объект.
 */
Stat::Stat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stat)
{
    ui->setupUi(this);
}

/**
 * @brief Деструктор класса Stat.
 */
Stat::~Stat()
{
    delete ui;
}

/**
 * @brief Слот для обработки сигнала slot1.
 * @param answer Ответ на вопрос 1.
 */
void Stat::slot1(QString answer)
{
    qDebug()<<"То, что сейчас в ответе вопрос 1: "<<answer;
    ui->label_Answer1->setText(answer);
}

/**
 * @brief Слот для обработки сигнала slot2.
 * @param answer Ответ на вопрос 2.
 */
void Stat::slot2(QString answer)
{
    qDebug()<<"То, что сейчас в ответе вопрос 2: "<<answer;
    ui->label_Answer2->setText(answer);
}

/**
 * @brief Слот для обработки сигнала slot3.
 * @param answer Ответ на вопрос 3.
 */
void Stat::slot3(QString answer)
{
    qDebug()<<"То, что сейчас в ответе вопрос 3: "<<answer;
    ui->label_Answer3->setText(answer);
}

/**
 * @brief Слот для обработки сигнала slot4.
 * @param answer Ответ на вопрос 4.
 */
void Stat::slot4(QString answer)
{
    qDebug()<<"То, что сейчас в ответе вопрос 4: "<<answer;
    ui->label_Answer4->setText(answer);
}
