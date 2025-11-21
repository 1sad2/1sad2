#ifndef SAFESIGNALPOOLS_H
#define SAFESIGNALPOOLS_H

#include <QObject>
#include <memory>
#include "safesignalmanager.h"
#include "signalpools_global.h"

class SIGNALPOOLSSHARED_EXPORT SafeSignalPools
{
public:
    static SafeSignalPools* instance();

    bool publish(const QString &topic,
                 QObject *pubObj,
                 const char *signal);

    bool subscribe(const QString &topic,
                   QObject *subObj,
                   const char *method,
                   Qt::ConnectionType type = Qt::AutoConnection);

    bool unPublish(const QString &topic);

    bool unSubscribe(const QString &topic,
                     QObject *subObj,
                     const char *method);

private:
    SafeSignalPools();

    std::unique_ptr<SafeSignalManager> manager;
};

#endif // SAFESIGNALPOOLS_H
