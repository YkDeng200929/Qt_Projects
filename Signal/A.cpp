#include "A.hpp"
#include <QDebug>

A::A(QObject *parent) : QObject(parent)
{

}

void A::slot_ASlot(QString qstr)
{
    qDebug() << "A槽函数调用" << qstr;
}
