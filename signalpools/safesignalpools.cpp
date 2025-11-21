#include "safesignalpools.h"

SafeSignalPools *SafeSignalPools::instance()
{
    static SafeSignalPools inst;
    return &inst;
}

bool SafeSignalPools::publish(const QString &topic, QObject *pubObj, const char *signal)
{
    return manager->publish(topic, pubObj, signal);
}

bool SafeSignalPools::subscribe(const QString &topic, QObject *subObj, const char *method, Qt::ConnectionType type)
{
    return manager->subscribe(topic, subObj, method, type);
}

bool SafeSignalPools::unPublish(const QString &topic)
{
    return manager->unPublish(topic);
}

bool SafeSignalPools::unSubscribe(const QString &topic, QObject *subObj, const char *method)
{
    return manager->unSubscribe(topic, subObj, method);
}

SafeSignalPools::SafeSignalPools()
    : manager(std::make_unique<SafeSignalManager>())
{

}
