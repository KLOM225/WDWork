#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(const QString &id, QObject *parent = nullptr);


    void sendMessage(const QString &message);;


signals:
    void sendMes(const QString &id, const QString &clientMes);

public slots:
    void ReceivedMes(const QString &id, const QString &clientMes);;

private:
    QString m_id;

};

#endif // CLIENT_H
