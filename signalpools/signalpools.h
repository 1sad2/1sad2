#ifndef SIGNALPOOLS_H
#define SIGNALPOOLS_H

#include "signalpools_global.h"
#include <QObject>
#include <QMutex>

#include <memory>

class SignalManager;
class SIGNALPOOLSSHARED_EXPORT SignalPools
{
public:
    static SignalPools *getInstance();
    bool publish(const QString &topic, QObject *pubObj, const char *signal);
    bool unPublish(const QString &topic);
    bool subscribe(const QString &topic, QObject *subObj, const char *method, Qt::ConnectionType type = Qt::AutoConnection);
    bool unSubscribe(const QString &topic, QObject *subObj, const char *method);

protected:
    SignalPools();
    ~SignalPools();

private:
    // 禁用拷贝和移动
    SignalPools(const SignalPools&) = delete;
    SignalPools& operator=(const SignalPools&) = delete;
    SignalPools(SignalPools&&) = delete;
    SignalPools& operator=(SignalPools&&) = delete;
private:
    std::unique_ptr<SignalManager> m_impManager;
    mutable QMutex m_mutex;
};

#endif // SIGNALPOOLS_H
