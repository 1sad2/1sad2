#ifndef SIGNALSUBSCRIBE_H
#define SIGNALSUBSCRIBE_H

#include <QObject>

class SignalSubscribe : public QObject
{
    Q_OBJECT
public:
    SignalSubscribe(QObject *subscribedObj, const QString &topic, const QString &method,
                    Qt::ConnectionType connectType = Qt::AutoConnection, QObject *parent = 0);
    QString getTopic() const;
    QString getMethod() const;
    QObject *getSubObj() const;
    Qt::ConnectionType getConnectType() const;
    friend bool operator == (const SignalSubscribe & subObj1,const SignalSubscribe & subObj2);
private:
    QObject *m_subObj;
    QString m_topic;
    QString m_method;
    Qt::ConnectionType m_connectType;
};

#endif // SIGNALSUBSCRIBE_H
