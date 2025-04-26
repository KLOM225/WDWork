#include "widget.h"

#include <QApplication>
#include "student.h"
#include <QDebug>
#include <QMetaObject>
#include <QMetaProperty>
#include <QMetaMethod>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    Student stu;

    QObject::connect(&stu, &Student::ageChanged, [](int age){
        qDebug() << "age" << age;
    });
    stu.setProperty("name", "LiSi");
    stu.setProperty("age", 20);



    const QMetaObject* meta = stu.metaObject();

    for(int i = 0; i < meta->propertyCount(); ++i){
        QMetaProperty prop = meta->property(i);
        qDebug() << "属性" << i + 1 << ":"
                 << prop.name()
                 << "类型:" << prop.typeName();
    }

    for(int i = 0; i < meta->methodCount(); ++i){
        //meta->method(i).methodSignature();
        QMetaMethod method = meta->method(i);
        qDebug() << "方法" << i + 1 << ":"
                 << method.methodSignature();
    }


    return a.exec();
}
