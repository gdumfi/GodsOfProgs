#include <QtTest>
#include "../Server/func_for_server.h"

// add necessary includes here

class qwe : public QObject
{
    Q_OBJECT

public:
    qwe();
    ~qwe();

private slots:
    void test_case1();
    void test_case2();
    void test_case3();
    void test_case4();
};

qwe::qwe()
{

}

qwe::~qwe()
{

}

void qwe::test_case1()
{
    QString params = "1;1;0;1;0;0;0;1";
    QCOMPARE(first_task(params),"(~A0U~A1U~A2)+(A0U~A1U~A2)+(A0UA1U~A2)+(A0UA1UA2)");
}

void qwe::test_case2()
{
    QString params = "1;1;0;1";
    QCOMPARE(second_task(params),"(A&B&~B)");
}

void qwe::test_case3()
{
    QString params = "1;1;1;0;1;0;1;0";
    QCOMPARE(third_task(params),"(x1 U !x2 U !x3 || !x1 U !x3)");
}

void qwe::test_case4()
{
    QString params = "0;1;1;1;1;1;1";
    QCOMPARE(fourth_task(params),"(A3+~A2)");
}

QTEST_APPLESS_MAIN(qwe)

#include "tst_qwe.moc"
