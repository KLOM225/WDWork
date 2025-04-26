#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QDebug>

class Counter : public QObject
{
    Q_OBJECT
public:
    explicit Counter(QObject *parent = nullptr);

signals:
    void valueChanged(int value);

public slots:
    void setValue(int newvalue);

private:
    int m_value;

};

#endif // COUNTER_H
