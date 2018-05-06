#ifndef TEST_H
#define TEST_H

#include <QtCore/QObject>
#include "qxsys/qxlagmeter.h"

class Test : public QObject
{
    Q_OBJECT

public:
    explicit Test(QObject *parent = 0);

    void exec();

private:
    QxLagMeter m_lagMeter;

    void testProcessProber();
    void testOsProber();
    void testPathProber();
    void testLagMeter();
    void testCloseDialog();
    void testLog();

private slots:
    void processLag(int ms);
};

#endif // TEST_H
