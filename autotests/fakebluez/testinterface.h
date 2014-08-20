#ifndef TESTINTERFACE_H
#define TESTINTERFACE_H

#include <QDBusAbstractAdaptor>

class FakeBluez;

class TestInterface : public QDBusAbstractAdaptor
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.qbluez.fakebluez.Test")

public:
    explicit TestInterface(FakeBluez *parent);

public Q_SLOTS:
    void runTest(const QString &testName);

private:
    FakeBluez *m_fakeBluez;
};

#endif // TESTINTERFACE_H