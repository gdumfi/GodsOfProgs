#ifndef STAT_H
#define STAT_H

#include <QWidget>

namespace Ui {
class Stat;
}

class Stat : public QWidget
{
    Q_OBJECT

public:
    explicit Stat(QWidget *parent = nullptr);
    ~Stat();

private:
    Ui::Stat *ui;

public slots:
    void slot1(QString answer);
    void slot2(QString answer);
    void slot3(QString answer);
    void slot4(QString answer);
};

#endif // STAT_H
