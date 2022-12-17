#include "MyThread.hpp"
#include <QDebug>

MyThread::MyThread(QObject *parent) : QThread(parent)
{
    isRun = false;
}

void MyThread::run()
{
    isRun = true;
    while(1)
    {
        if (!isRun)
        {
            break;
        }
        sleep(1);
        qDebug() << "线程正在执行";
    }
}

void MyThread::KILL()
{
    isRun = false;
}
