#include "student.h"
#include <QDebug>

Student::Student(QObject *parent) : QObject(parent)
{

}

void Student::eat()
{
    qDebug() << "吃饭";
}

