#ifndef QBLUEZ_ADAPTER_H
#define QBLUEZ_ADAPTER_H

#include <QObject>
#include <QList>
#include <QStringList>

#include "qbluez_export.h"

namespace QBluez
{

class Device;
class PendingCall;

/**
 * Bluetooth adapter.
 *
 * This class represents a Bluetooth adapter.
 */
class QBLUEZ_EXPORT Adapter : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString ubi READ ubi)
    Q_PROPERTY(QString address READ address)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QString alias READ alias WRITE setAlias NOTIFY aliasChanged)
    Q_PROPERTY(quint32 adapterClass READ adapterClass NOTIFY adapterClassChanged)
    Q_PROPERTY(bool powered READ isPowered WRITE setPowered NOTIFY poweredChanged)
    Q_PROPERTY(bool discoverable READ isDiscoverable WRITE setDiscoverable NOTIFY discoverableChanged)
    Q_PROPERTY(quint32 discoverableTimeout READ discoverableTimeout WRITE setDiscoverableTimeout NOTIFY discoverableTimeoutChanged)
    Q_PROPERTY(bool pairable READ isPairable WRITE setPairable NOTIFY pairableChanged)
    Q_PROPERTY(quint32 pairableTimeout READ pairableTimeout WRITE setPairableTimeout NOTIFY pairableTimeoutChanged)
    Q_PROPERTY(bool discovering READ isDiscovering NOTIFY discoveringChanged)
    Q_PROPERTY(QStringList uuids READ uuids NOTIFY uuidsChanged)
    Q_PROPERTY(QString modalias READ modalias NOTIFY modaliasChanged)
    Q_PROPERTY(QList<QBluez::Device*> devices READ devices)

public:
    /**
     * Destroys an Adapter object.
     */
    virtual ~Adapter();

    /**
     * Returns an UBI of the adapter.
     *
     * Example UBI: "/org/bluez/hci0"
     *
     * @return UBI of adapter
     */
    QString ubi() const;

    /**
     * Returns an address of the adapter.
     *
     * Example address: "1C:E5:C3:BC:94:7E"
     *
     * @return address of adapter
     */
    QString address() const;

    /**
     * Returns a name of the adapter.
     *
     * @return name of adapter
     */
    QString name() const;

    /**
     * Returns an alias of the adapter.
     *
     * @return alias of adapter
     */
    QString alias() const;

    /**
     * Sets the alias for the adapter.
     *
     * @param alias alias for adapter
     * @return void pending call
     */
    PendingCall *setAlias(const QString &alias);

    /**
     * Returns a class of the adapter.
     *
     * @return class of adapter
     */
    quint32 adapterClass() const;

    /**
     * Returns whether the adapter is powered on.
     *
     * @return true if adapter is powered on
     */
    bool isPowered() const;

    /**
     * Sets the powered state of the adapter.
     *
     * @param powered powered state
     * @return void pending call
     */
    PendingCall *setPowered(bool powered);

    /**
     * Returns whether the adapter is discoverable by other devices.
     *
     * @return true if adapter is discoverable
     */
    bool isDiscoverable() const;

    /**
     * Sets the discoverable state of the adapter.
     *
     * @param discoverable discoverable state
     * @return void pending call
     */
    PendingCall *setDiscoverable(bool discoverable);

    /**
     * Returns the discoverable timeout in seconds of the adapter.
     *
     * Discoverable timeout defines how long the adapter stays in
     * discoverable state after calling setDiscoverable(true).
     *
     * Timeout 0 means infinitely.
     *
     * @return discoverable timeout of adapter
     */
    quint32 discoverableTimeout() const;

    /**
     * Sets the discoverable timeout of the adapter.
     *
     * @param timeout timeout in seconds
     * @return void pending call
     */
    PendingCall *setDiscoverableTimeout(quint32 timeout);

    /**
     * Returns whether the adapter is pairable with other devices.
     *
     * @return true if adapter is pairable
     */
    bool isPairable() const;

    /**
     * Sets the pairable state of the adapter.
     *
     * @param pairable pairable state
     * @return void pending call
     */
    PendingCall *setPairable(bool pairable);

    /**
     * Returns the pairable timeout in seconds of the adapter.
     *
     * Pairable timeout defines how long the adapter stays in
     * pairable state after calling setPairable(true).
     *
     * Timeout 0 means infinitely.
     *
     * @return pairable timeout of adapter
     */
    quint32 pairableTimeout() const;

    /**
     * Sets the pairable timeout of the adapter.
     *
     * @param timeout timeout in seconds
     * @return void pending call
     */
    PendingCall *setPairableTimeout(quint32 timeout);

    /**
     * Returns whether the adapter is discovering for other devices
     *
     * @return true if adapter is discovering
     */
    bool isDiscovering();

    /**
     * Returns UUIDs of available services.
     *
     * @return UUIDs of available services
     */
    QStringList uuids() const;

    /**
     * Returns local device ID in modalias format.
     *
     * @return adapter modalias
     */
    QString modalias() const;

    /**
     * Returns list of devices known by the adapter.
     *
     * @return list of devices
     */
    QList<Device*> devices() const;

public Q_SLOTS:
    /**
     * Returns a device for specified address.
     *
     * @param address address of device (eg. "40:79:6A:0C:39:75")
     * @return null if there is no device with specified address
     */
    QBluez::Device *deviceForAddress(const QString &address) const;

    /**
     * Starts device discovery.
     *
     * Possible errors: PendingCall::NotReady, PendingCall::Failed
     *
     * @return void pending call
     * @see discoverableTimeout()
     */
    QBluez::PendingCall *startDiscovery();

    /**
     * Stops device discovery.
     *
     * Possible errors: PendingCall::NotReady, PendingCall::Failed, PendingCall::NotAuthorized
     *
     * @return void pending call
     */
    QBluez::PendingCall *stopDiscovery();

    // Possible errors:
    /**
     * Removes the specified device.
     *
     * It will also remove the pairint information.
     *
     * Possible errors: PendingCall::InvalidArguments, PendingCall::Failed
     *
     * @param device device to be removed
     * @return void pending call
     */
    QBluez::PendingCall *removeDevice(QBluez::Device *device);

Q_SIGNALS:
    /**
     * Indicates that at least one of the adapter's property have changed.
     */
    void adapterChanged(QBluez::Adapter *adapter);

    /**
     * Indicates that adapter's name have changed.
     */
    void nameChanged(const QString &name);

    /**
     * Indicates that adapter's alias have changed.
     */
    void aliasChanged(const QString &name);

    /**
     * Indicates that adapter's class have changed.
     */
    void adapterClassChanged(quint32 adapterClass);

    /**
     * Indicates that adapter's powered state have changed.
     */
    void poweredChanged(bool powered);

    /**
     * Indicates that adapter's discoverable state have changed.
     */
    void discoverableChanged(bool discoverable);

    /**
     * Indicates that adapter's discoverable timeout have changed.
     */
    void discoverableTimeoutChanged(quint32 timeout);

    /**
     * Indicates that adapter's pairable state have changed.
     */
    void pairableChanged(bool pairable);

    /**
     * Indicates that adapter's pairable timeout have changed.
     */
    void pairableTimeoutChanged(quint32 timeout);

    /**
     * Indicates that adapter's discovering state have changed.
     */
    void discoveringChanged(bool discovering);

    /**
     * Indicates that adapter's UUIDs have changed.
     */
    void uuidsChanged(const QStringList &uuids);

    /**
     * Indicates that adapter's modalias have changed.
     */
    void modaliasChanged(const QString &modalias);

    /**
     * Indicates that a new device have been found.
     */
    void deviceFound(QBluez::Device *device);

    /**
     * Indicates that a device have been removed.
     */
    void deviceRemoved(QBluez::Device *device);

    /**
     * Indicates that at least one of the device's property have changed.
     */
    void deviceChanged(QBluez::Device *device);

private:
    explicit Adapter(const QString &address, const QVariantMap &properties, QObject *parent);

    class AdapterPrivate *const d;

    friend class AdapterPrivate;
    friend class ManagerPrivate;
    friend class InitAdaptersJobPrivate;
};

} // namespace QBluez

#endif // QBLUEZ_ADAPTER_H
