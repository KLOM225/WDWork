#include "counter.h"

Counter::Counter(QObject *parent) : QObject(parent)
{

}

void Counter::setValue(int newvalue)
{
    if(m_value != newvalue){
        m_value = newvalue;
        emit valueChanged(m_value);
        qDebug() << "[debug] value" << m_value;
    }
}
