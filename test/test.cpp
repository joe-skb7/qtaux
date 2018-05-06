#include <QtGui/QApplication>
#include <QtCore/QDebug>
#include "test.h"
#include "qxgui/qxclosedialog.h"
#include "qxsys/qxosprober.h"
#include "qxsys/qxpathprober.h"
#include "qxsys/qxprocessprober.h"
#include "qxutil/qxlogwriter.h"

Test::Test(QObject *parent)
    : QObject(parent)
{
}

void Test::exec()
{
//    testProcessProber();
//    testOsProber();
//    testPathProber();
//    testLagMeter();
    testLog();
    testCloseDialog();

    exit(0);
}

/* private */

void Test::testProcessProber()
{
    QxProcessProber pp;
    pp.refreshProcessList();
    qDebug() << pp.processList().join("\n");
}

void Test::testOsProber()
{
    qDebug() << QxOsProber::osName();
}

void Test::testPathProber()
{
    qDebug() << QxPathProber::configDirPath();
}

void Test::testLagMeter()
{
    QObject::connect(&m_lagMeter, SIGNAL(lagReceived(int)),
                     this, SLOT(processLag(int)));
    m_lagMeter.ping("8.8.8.8");
}

void Test::testCloseDialog()
{
    QxCloseDialog::askUser(0, "title", "appname");
}

void Test::testLog()
{
    qxAppLogger().setFilePath("/tmp/log.dat");
    qxAppLogger().setHeader(QxLogWriter::TimeHeader | QxLogWriter::LevelHeader
                  | QxLogWriter::CustomHeader);
    qxAppLogger().setCustomHeader("{look it my log, my log is amazing!} ");
    qxAppLogger().write("first message");
    qxAppLogger().write("second message");
}

/* private slots */

void Test::processLag(int ms)
{
    qDebug() << "Lag: " << ms << " ms";
}
