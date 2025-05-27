#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class Student : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)   // 可读写name属性
    Q_PROPERTY(int age READ age WRITE setAge NOTIFY ageChanged)  // 可读写age属性，带信号

public:
    explicit Student(QObject *parent = nullptr);

    QString name()const
    {
        return m_name;
    }

    void setName(const QString &name){
        m_name = name;
    }

    int age() const {
        return m_age;
    }

    void setAge(const int age){
        m_age = age;
        emit ageChanged(m_age);.

    }


signals:
    void ageChanged(int age);

private:
    QString m_name;
    int m_age;
};

#endif // STUDENT_H
