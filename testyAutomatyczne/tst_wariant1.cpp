#include <QtTest>

// add necessary includes here

class Wariant1 : public QObject
{
    Q_OBJECT

public:
    Wariant1();
    ~Wariant1();

private slots:
    void test_case1();

};

Wariant1::Wariant1()
{

}

Wariant1::~Wariant1()
{

}

void Wariant1::test_case1()
{

}

QTEST_APPLESS_MAIN(Wariant1)

#include "tst_wariant1.moc"
