#include "signalsubscribe.h"

SignalSubscribe::SignalSubscribe(QObject *subscribedObj, const QString &topic, const QString &method,
                                 Qt::ConnectionType connectType, QObject *parent)
    : QObject(parent)
    , m_subObj(subscribedObj)
    , m_topic(topic)
    , m_method(method)
    , m_connectType(connectType)
{

}

QString SignalSubscribe::getTopic() const
{
    return m_topic;
}

QString SignalSubscribe::getMethod() const
{
     return m_method;
}

QObject *SignalSubscribe::getSubObj() const
{
    return m_subObj.data();
}

Qt::ConnectionType SignalSubscribe::getConnectType() const
{
    return m_connectType;
}
bool operator ==(const SignalSubscribe &subObj1, const SignalSubscribe &subObj2)
{
    return (subObj1.m_subObj == subObj2.m_subObj &&
            subObj1.m_topic == subObj2.m_topic &&
            subObj1.m_method == subObj2.m_method &&
            subObj1.m_connectType == subObj2.m_connectType);
}
