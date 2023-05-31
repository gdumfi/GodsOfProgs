/* #include "check_tests.h"
#include "func_for_server.h"
#include "mytcpserver.h"

check_tests::check_tests(QObject *parent)
    : QObject{parent}
{

}

void check_tests::test_case1()
{
    QString params = 0,1,2,3,4,5,6,7;
    QCOMPARE(Dual(params),"11111111");
}

void check_tests::test_case2()
{
    QStringList params = 1;
    QCOMPARE(Dual(params),"10");
}

void check_tests::test_case3()
{
    QStringList params = 7,8,9;
    QCOMPARE(Dual(params),"0000001110000000");
}

void check_tests::test_case4()
{
    QStringList params = 0,2,5;
    QCOMPARE(Dual(params),"00100101");
}

QTEST_MAIN(check_tests)*/
