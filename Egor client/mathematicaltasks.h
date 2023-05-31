#ifndef MATHEMATICALTASKS_H
#define MATHEMATICALTASKS_H

#include <QWidget>
#include <QString>
#include <QList>
#include <stat.h>

namespace Ui {
class MathematicalTasks;
}

class MathematicalTasks : public QWidget
{
    Q_OBJECT

public:
    explicit MathematicalTasks(QWidget *parent = nullptr);
    ~MathematicalTasks();

private slots:
    void on_pushButton_Exit_clicked();

    void on_pushButton_Next_clicked();

    void on_pushButton_Back_clicked();

    void on_pushButton_Stat_clicked();

private:
    Ui::MathematicalTasks *ui;
    MathematicalTasks *MathematicalTasksWindow;
    Stat *stat;
    QStringList params; // Это будет список правильных ответов, с которыми будут сравниваться ответы пользователей
    QStringList random;

    void resolve_stat();
    void getanswers();
    QString gettask(int num);

signals:
    void signal1(QString answer);
    void signal2(QString answer);
    void signal3(QString answer);
    void signal4(QString answer);
};

#endif // MATHEMATICALTASKS_H
