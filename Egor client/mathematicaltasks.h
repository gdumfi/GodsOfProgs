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


    void resolve_stat();

signals:
    void signal1(QString answer);
    void signal2(QString answer);
    void signal3(QString answer);
    void signal4(QString answer);
};

#endif // MATHEMATICALTASKS_H
