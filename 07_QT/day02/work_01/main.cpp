#include "widget.h"

#include <QApplication>
#include <counter.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    Counter cot;

    QObject::connect(&cot, &Counter::valueChanged, [](int value){
        qDebug() << "value: " << value;
    });

    cot.setValue(10);

    return a.exec();
}
