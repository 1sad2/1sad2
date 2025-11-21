#include "safepublisher.h"

SafePublisher::SafePublisher(QObject *obj, const QString &signal)
    : sender(obj), signalName(signal)
{}

bool SafePublisher::isValid() const
{
    return !sender.isNull();
}
