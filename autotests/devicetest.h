#ifndef DEVICETEST_H
#define DEVICETEST_H

#include <QObject>
#include <QList>

#include "bluezdevice1_tst.h"
#include "dbusproperties_tst.h"

#include "manager.h"
#include "adapter.h"
#include "device.h"

class DeviceTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void getPropertiesTest();
    void setAliasTest();
    void setTrustedTest();
    void setBlockedTest();

private:
    struct DeviceUnit
    {
        QBluez::Device *device;
        org::bluez::Device1 *dbusDevice;
        org::freedesktop::DBus::Properties *dbusProperties;
    };

    QList<DeviceUnit> m_units;
};

#endif // DEVICETEST_H