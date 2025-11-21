#ifndef SAFESIGNALMANAGER_H
#define SAFESIGNALMANAGER_H

#include <QObject>
#include <QMap>
#include <QReadWriteLock>
#include <QSharedPointer>
#include "safepublisher.h"

class SafeSignalManager : public QObject
{
    Q_OBJECT
public:
    explicit SafeSignalManager(QObject *parent = nullptr);

    bool publish(const QString &topic,
                 QObject *pubObj,
                 const QString &signal);

    bool unPublish(const QString &topic);

    bool subscribe(const QString &topic,
                   QObject *subObj,
                   const QString &method,
                   Qt::ConnectionType type = Qt::AutoConnection);

    bool unSubscribe(const QString &topic,
                     QObject *subObj,
                     const QString &method);

private:
    bool connectOne(SafePublisher *pub,
                    const QSharedPointer<SafeSubscriber> &sub);

    bool disconnectOne(SafePublisher *pub,
                       const QSharedPointer<SafeSubscriber> &sub);

private:
    QMap<QString, QSharedPointer<SafePublisher>> pubMap;
    QMap<QString, QList<QSharedPointer<SafeSubscriber>>> pendingSubs;

    mutable QReadWriteLock lock;
};

#endif // SAFESIGNALMANAGER_H
