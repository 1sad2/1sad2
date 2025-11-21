#ifndef SAFESUBSCRIBER_H
#define SAFESUBSCRIBER_H

#include <QObject>
#include <QPointer>

class SafeSubscriber
{
public:
    SafeSubscriber(QObject *obj,
                   const QString &method,
                   Qt::ConnectionType type);

    bool isValid() const;

    QPointer<QObject> receiver;
    QString methodName;
    Qt::ConnectionType connType;

private:
    Q_DISABLE_COPY(SafeSubscriber)
};

#endif // SAFESUBSCRIBER_H
