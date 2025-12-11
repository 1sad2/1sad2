#ifndef SIGNALPUBLISH_H
#define SIGNALPUBLISH_H

#include <QObject>
#include <QPointer>

class SignalSubscribe;
class SignalPublish : public QObject
{
    Q_OBJECT
public:
    SignalPublish(const QString &topic,QObject *publishObj,
                  const QString &signal,QObject *parent = 0);
    bool subsribe(SignalSubscribe *sub);
    bool unSubsrcibe(SignalSubscribe *sub);
    QList<SignalSubscribe *> getAllSubList();

private:
    QPointer<QObject> m_pubObj;
    QString m_topic;
    QString m_signal;
    QList<SignalSubscribe *> m_subObjList;
};

#endif // SIGNALPUBLISH_H
