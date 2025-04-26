#include "widget.h"

#include <QApplication>
#include "client.h"
#include "messagebus.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    MessageBus mBus;

    Client client1("Client1");
    Client client2("Client2");

    mBus.connectClient(&client1, "Client1");
    mBus.connectClient(&client2, "Client2");


    client1.sendMessage("Hello");
    client2.sendMessage("world");


    return a.exec();
}
