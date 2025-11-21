#include "safesubscriber.h"

SafeSubscriber::SafeSubscriber(QObject *obj, const QString &method, Qt::ConnectionType type)
    : receiver(obj),
      methodName(method),
      connType(type)
{}

bool SafeSubscriber::isValid() const
{
    return !receiver.isNull();
}
