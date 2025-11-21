#include "safesignalmanager.h"

SafeSignalManager::SafeSignalManager(QObject *parent)
    : QObject(parent)
{
}

bool SafeSignalManager::publish(const QString &topic,
                                QObject *pubObj,
                                const QString &signal)
{
    if (topic.isEmpty() || !pubObj)
        return false;

    QWriteLocker locker(&lock);

    if (pubMap.contains(topic))
        return false;

    auto pub = QSharedPointer<SafePublisher>::create(pubObj, signal);
    pubMap.insert(topic, pub);

    // connect pending subscribers
    if (pendingSubs.contains(topic))
    {
        for (auto &sub : pendingSubs[topic])
            connectOne(pub.data(), sub);
        pendingSubs.remove(topic);
    }

    return true;
}

bool SafeSignalManager::unPublish(const QString &topic)
{
    QWriteLocker locker(&lock);

    if (!pubMap.contains(topic))
        return false;

    auto pub = pubMap[topic];

    for (auto &sub : pub->subscribers)
        disconnectOne(pub.data(), sub);

    pubMap.remove(topic);
    return true;
}

bool SafeSignalManager::subscribe(const QString &topic,
                                  QObject *subObj,
                                  const QString &method,
                                  Qt::ConnectionType type)
{
    if (topic.isEmpty() || !subObj)
        return false;

    QWriteLocker locker(&lock);

    auto sub = QSharedPointer<SafeSubscriber>::create(subObj, method, type);

    if (pubMap.contains(topic))
    {
        auto pub = pubMap[topic];
        return connectOne(pub.data(), sub);
    }

    pendingSubs[topic].append(sub);
    return true;
}

bool SafeSignalManager::unSubscribe(const QString &topic,
                                    QObject *subObj,
                                    const QString &method)
{
    if (!subObj)
        return false;

    QWriteLocker locker(&lock);

    if (!pubMap.contains(topic))
    {
        auto &list = pendingSubs[topic];
        for (int i = list.size() - 1; i >= 0; --i)
        {
            if (list[i]->receiver == subObj &&
                list[i]->methodName == method)
            {
                list.removeAt(i);
                return true;
            }
        }
        return false;
    }

    auto pub = pubMap[topic];
    auto &list = pub->subscribers;

    for (int i = list.size() - 1; i >= 0; --i)
    {
        if (list[i]->receiver == subObj &&
            list[i]->methodName == method)
        {
            disconnectOne(pub.data(), list[i]);
            list.removeAt(i);
            return true;
        }
    }

    return false;
}

bool SafeSignalManager::connectOne(SafePublisher *pub,
                                   const QSharedPointer<SafeSubscriber> &sub)
{
    if (!pub->isValid() || !sub->isValid())
        return false;

    QByteArray sig = pub->signalName.toUtf8();
    QByteArray mth = sub->methodName.toUtf8();

    bool ok = QObject::connect(
        pub->sender, sig.data(),
        sub->receiver, mth.data(),
        sub->connType);

    if (ok)
        pub->subscribers.append(sub);

    return ok;
}

bool SafeSignalManager::disconnectOne(SafePublisher *pub,
                                      const QSharedPointer<SafeSubscriber> &sub)
{
    if (!pub->isValid())
        return false;

    QByteArray sig = pub->signalName.toUtf8();
    QByteArray mth = sub->methodName.toUtf8();

    QObject::disconnect(
        pub->sender, sig.data(),
        sub->receiver, mth.data());

    return true;
}
