#ifndef SIGNALMANAGER_H
#define SIGNALMANAGER_H

#include <QObject>
#include <QPointer>
#include <QMap>
#include <QList>
#include <QMutex>
#include <memory>

class SignalManager : public QObject
{
    Q_OBJECT

public:
    explicit SignalManager(QObject *parent = nullptr);

    bool publish(const QString &topic, QObject *pubObj, const char *signal);
    bool unPublish(const QString &topic);

    bool subscribe(const QString &topic, QObject *subObj, const char *method,
                   Qt::ConnectionType type = Qt::AutoConnection);

    bool unSubscribe(const QString &topic, QObject *subObj, const char *method);

private:
    struct Publisher
    {
        QString topic;
        QPointer<QObject> obj;
        QByteArray signal;
    };

    struct Subscriber
    {
        QPointer<QObject> obj;
        QByteArray method;
        Qt::ConnectionType type = Qt::AutoConnection;
    };

private:
    QMutex m_mutex;

    QMap<QString, std::shared_ptr<Publisher>> m_pubMap;
    QMap<QString, QList<std::shared_ptr<Subscriber>>> m_subMap;

    void cleanDeadSubscribers(const QString &topic);
    void cleanDeadPublisher(const QString &topic);
};

#endif // SIGNALMANAGER_H
