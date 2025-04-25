#include "widget.h"
#include <QPushButton>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 800);
    QPushButton * pb = new QPushButton("第一个按键" ,this);
    pb->move(100,200);

    connect(pb, &QPushButton::clicked, this, &QPushButton::close);
    qDebug() << "按键";
    connect(pb, &QPushButton::clicked, []{
        qDebug() << "点击按键，让窗口关闭";
    });

}

Widget::~Widget()
{
}

