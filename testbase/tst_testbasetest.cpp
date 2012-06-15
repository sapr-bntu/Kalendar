#include <QtCore/QString>
#include <QtTest/QtTest>
#include <QDialog>
#include <QtSql>
#include <QSystemTrayIcon>
#include <QtCore/QCoreApplication>
#include "../dialog.h"

class TestbaseTest : public QObject
{
    Q_OBJECT

public:
    TestbaseTest();

private Q_SLOTS:
    void testCase1();    


    void on_pushButton_clicked();
    void delete1();


    void process();
};

TestbaseTest::TestbaseTest()
{
}

void TestbaseTest::testCase1()
{
    QVERIFY2(true, "Failure");
}


void TestbaseTest::on_pushButton_clicked()
{
    Dialog obj1;
    bool flag=obj1.on_pushButton_clicked();
    QCOMPARE(true,flag);
}
void TestbaseTest::delete1()
{
    Dialog obj1;
    bool flag=obj1.delete1();
    QCOMPARE(true,flag);
}

void TestbaseTest:: process()
{
    Dialog obj1;
    bool flag=obj1.process();
    QCOMPARE(true,flag);
}


QTEST_MAIN(TestbaseTest);

#include "tst_testbasetest.moc"
