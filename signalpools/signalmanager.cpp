#include "signalmanager.h"
#include <QMutexLocker>
#include <QDebug>

SignalManager::SignalManager(QObject *parent)
    : QObject(parent)
{
}

bool SignalManager::publish(const QString &topic, QObject *pubObj, const char *signal)
{
    QMutexLocker locker(&m_mutex);

    if (topic.isEmpty() || pubObj == nullptr || signal == nullptr)
        return false;

    cleanDeadPublisher(topic);

    // 一个 topic 只能有一个发布者
    if (m_pubMap.contains(topic))
        return false;

    auto pub = std::make_shared<Publisher>();
    pub->topic = topic;
    pub->obj = pubObj;
    pub->signal = signal;

    m_pubMap.insert(topic, pub);

    // 连接已有的订阅者
    auto subs = m_subMap.value(topic);
    for (auto &sub : subs)
    {
        if (!sub->obj)
            continue;

        bool ok = QObject::connect(
            pubObj, signal,
            sub->obj, sub->method.constData(),
            sub->type);

        if (!ok)
            qWarning() << "Connect failed (publish)" << topic << signal << sub->method;
    }

    return true;
}

bool SignalManager::unPublish(const QString &topic)
{
    QMutexLocker locker(&m_mutex);

    if (!m_pubMap.contains(topic))
        return false;

    auto pub = m_pubMap[topic];

    if (pub && pub->obj)
    {
        // disconnect all subscribers
        auto subs = m_subMap.value(topic);
        for (auto &sub : subs)
        {
            if (sub->obj)
            {
                QObject::disconnect(
                    pub->obj, pub->signal.constData(),
                    sub->obj, sub->method.constData());
            }
        }
    }

    m_pubMap.remove(topic);
    return true;
}

bool SignalManager::subscribe(const QString &topic, QObject *subObj, const char *method,
                              Qt::ConnectionType type)
{
    QMutexLocker locker(&m_mutex);

    if (topic.isEmpty() || subObj == nullptr || method == nullptr)
        return false;

    cleanDeadSubscribers(topic);

    // 检查是否重复订阅
    auto &lst = m_subMap[topic];
    for (auto &s : lst)
    {
        if (s->obj == subObj && s->method == method)
        {
            return false;  // 已订阅
        }
    }

    auto sub = std::make_shared<Subscriber>();
    sub->obj = subObj;
    sub->method = method;
    sub->type = type;

    lst.append(sub);

    // 如果已有发布者，则立即 connect
    if (m_pubMap.contains(topic))
    {
        auto pub = m_pubMap[topic];
        if (pub->obj)
        {
            bool ok = QObject::connect(
                pub->obj, pub->signal.constData(),
                subObj, method,
                type);

            if (!ok)
                qWarning() << "Connect failed (subscribe)" << topic << pub->signal << method;
        }
    }

    return true;
}

bool SignalManager::unSubscribe(const QString &topic, QObject *subObj, const char *method)
{
    QMutexLocker locker(&m_mutex);

    if (!m_subMap.contains(topic))
        return false;

    auto &lst = m_subMap[topic];

    for (int i = 0; i < lst.size(); ++i)
    {
        auto sub = lst[i];

        if (sub->obj == subObj && sub->method == method)
        {
            // disconnect if publisher exists
            if (m_pubMap.contains(topic))
            {
                auto pub = m_pubMap[topic];
                if (pub->obj && subObj)
                {
                    QObject::disconnect(
                        pub->obj, pub->signal.constData(),
                        subObj, method);
                }
            }

            lst.removeAt(i);
            return true;
        }
    }

    return false;
}

void SignalManager::cleanDeadSubscribers(const QString &topic)
{
    auto &lst = m_subMap[topic];
    for (int i = lst.size() - 1; i >= 0; --i)
    {
        if (lst[i]->obj == nullptr)
            lst.removeAt(i);
    }
}

void SignalManager::cleanDeadPublisher(const QString &topic)
{
    auto pub = m_pubMap.value(topic);
    if (pub && pub->obj == nullptr)
        m_pubMap.remove(topic);
}
