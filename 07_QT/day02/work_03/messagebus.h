#ifndef MESSAGEBUS_H
#define MESSAGEBUS_H

#include <QObject>
#include "client.h"
#include <QString>
#include <QMap>
#include <QDebug>

class MessageBus : public QObject
{
    Q_OBJECT

public:
    explicit MessageBus(QObject *parent = nullptr);

    void connectClient(Client * client, const QString & clientID);

public slots:
    void ReceivedBus(const QString &senderID, const QString &clientMes);;

signals:

    void sendBus(const QString &clientID, const QString &clientMes);
};

#endif // MESSAGEBUS_H
