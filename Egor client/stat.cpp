#include "stat.h"
#include "ui_stat.h"

Stat::Stat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Stat)
{
    ui->setupUi(this);
}

Stat::~Stat()
{
    delete ui;
}

void Stat::slot1(QString answer)
{
    qDebug()<<"То, что сейчас в ответе вопрос 1: "<<answer;
    ui->label_Answer1->setText(answer);
}

void Stat::slot2(QString answer)
{
    qDebug()<<"То, что сейчас в ответе вопрос 2: "<<answer;
    ui->label_Answer2->setText(answer);
}

void Stat::slot3(QString answer)
{
    qDebug()<<"То, что сейчас в ответе вопрос 3: "<<answer;
    ui->label_Answer3->setText(answer);
}

void Stat::slot4(QString answer)
{
    qDebug()<<"То, что сейчас в ответе вопрос 4: "<<answer;
    ui->label_Answer4->setText(answer);
}
