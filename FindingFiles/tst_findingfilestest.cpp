#include <QString>
#include <QtTest>

class FindingFilesTest : public QObject
{
    Q_OBJECT

public:
    FindingFilesTest();

private Q_SLOTS:
    void testCase1();
};

FindingFilesTest::FindingFilesTest()
{
}

void FindingFilesTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(FindingFilesTest)

#include "tst_findingfilestest.moc"
