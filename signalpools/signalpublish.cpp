#include "signalpublish.h"
#include "signalsubscribe.h"
SignalPublish::SignalPublish( const QString &topic,QObject *publishObj,
                             const QString &signal,QObject *parent)
 : QObject(parent)
{
    m_pubObj = publishObj;
    m_topic = topic;
    m_signal = signal;
}

bool SignalPublish::subsribe(SignalSubscribe *sub)
{
    //主题不一致//
    if(sub->getTopic() != m_topic)
    {
        return false;
    }

    //已经订阅//
    for(int i=0;i<m_subObjList.count();++i)
    {
        SignalSubscribe *subRegisted= m_subObjList[i];
        if(*subRegisted == *sub)
        {
            return false;
        }
    }

    QObject *sender = m_pubObj;    
    QByteArray signalByte = m_signal.toUtf8();
    const char *signal = signalByte.data();
    QObject *receiver = sub->getSubObj();
    QByteArray methodByte = sub->getMethod().toUtf8();
    const char *method = methodByte.data();
    Qt::ConnectionType type = sub->getConnectType();
    if(connect(sender,signal,receiver,method,type))
    {
        m_subObjList.append(sub);
    }
    return true;
}

bool SignalPublish::unSubsrcibe(SignalSubscribe *sub)
{
    //主题不一致//
    if(sub->getTopic() != m_topic)
    {
        return false;
    }

    //已经订阅//
    for(int i=0;i<m_subObjList.count();++i)
    {
        SignalSubscribe *subRegisted= m_subObjList[i];
        if(*subRegisted == *sub)
        {
            QObject *sender = m_pubObj;
            const char *signal = m_signal.toUtf8().data();
            QObject *receiver = subRegisted->getSubObj();
            const char *method = subRegisted->getMethod().toUtf8().data();
            disconnect(sender,signal,receiver,method);
            delete subRegisted;
            return true;
        }
    }
    return false;
}

QList<SignalSubscribe *> SignalPublish::getAllSubList()
{
    return m_subObjList;
}
