#include "messagebus.h"

MessageBus::MessageBus(QObject *parent)
    : QObject(parent)
{

}

void MessageBus::connectClient(Client *client, const QString &clientID){

    connect(client, &Client::sendMes, this, &MessageBus::ReceivedBus);

    connect(this, &MessageBus::sendBus, client, &Client::ReceivedMes);

    qDebug() << "Client registered:" << clientID;
}


void MessageBus::ReceivedBus(const QString &senderID, const QString &clientMes){

    qDebug() << "MessageBus forwarding message from" << senderID << ":" << clientMes;

    emit sendBus(senderID, clientMes);
}
