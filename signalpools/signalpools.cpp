#include "signalpools.h"
#include "signalmanager.h"

SignalPools::SignalPools() : m_impManager(std::make_unique<SignalManager>())
{
}

SignalPools::~SignalPools()
{
}

SignalPools *SignalPools::getInstance()
{
    static SignalPools instance;
    return &instance;
}

bool SignalPools::publish(const QString &topic, QObject *pubObj, const char *signal)
{
    QMutexLocker locker(&m_mutex);

    if(!m_impManager || !pubObj || !signal || topic.isEmpty())
    {
        return false;
    }

    return m_impManager->publish(topic, pubObj, signal);
}

bool SignalPools::unPublish(const QString &topic)
{
    QMutexLocker locker(&m_mutex);

    if(!m_impManager)
    {
        return false;
    }

    return m_impManager->unPublish(topic);
}

bool SignalPools::subscribe(const QString &topic, QObject *subObj, const char *method, Qt::ConnectionType type)
{
    QMutexLocker locker(&m_mutex);

    if(!m_impManager || !subObj || !method || topic.isEmpty())
    {
        return false;
    }

    return m_impManager->subscribe(topic, subObj, method, type);
}

bool SignalPools::unSubscribe(const QString &topic, QObject *subObj, const char *method)
{
    QMutexLocker locker(&m_mutex);

    if(!m_impManager)
    {
        return false;
    }

    return m_impManager->unSubscribe(topic, subObj, method);
}
