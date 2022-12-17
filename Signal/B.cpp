#include "B.hpp"
#include <QDebug>

B::B(QObject *parent) : QObject(parent)
{

}

void B::slot_BSlot(QString qstr)
{
    qDebug() << "B槽函数调用" << qstr;
}
