#include "widget.h"
#include "ui_widget.h"
#include <QtDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_tech = new Teacher;
    m_stu = new Student;

    //connect(m_tech, &Teacher::treat, m_stu, &Student::eat);
    connect(m_tech, &Teacher::treat, []{
            qDebug() << "请学生吃大米饭";
        });
    freetime();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::freetime()
{
    emit m_tech->treat();

}

