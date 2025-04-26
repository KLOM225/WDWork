#include "client.h"


Client::Client(const QString &id, QObject *parent)
    :QObject(parent), m_id(id)
{

}

void Client::sendMessage(const QString &message){
    qDebug() << m_id << "sent message:" << message;
    emit sendMes(m_id, message);

}

void Client::ReceivedMes(const QString &id, const QString &clientMes){

      if(id != m_id) {  // 不接收自己发送的消息
        qDebug() << m_id << "received from" << id << ":" << clientMes;
    }


}
