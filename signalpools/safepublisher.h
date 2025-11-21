#ifndef SAFEPUBLISHER_H
#define SAFEPUBLISHER_H

#include <QObject>
#include <QPointer>
#include <QList>
#include <QSharedPointer>
#include "safesubscriber.h"

class SafePublisher
{
public:
    SafePublisher(QObject *obj, const QString &signal);

    bool isValid() const;

    QPointer<QObject> sender;
    QString signalName;
    QList<QSharedPointer<SafeSubscriber>> subscribers;

private:
    Q_DISABLE_COPY(SafePublisher)
};

#endif // SAFEPUBLISHER_H
