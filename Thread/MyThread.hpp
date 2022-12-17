#ifndef MYTHREAD_HPP
#define MYTHREAD_HPP

#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

    void run();  // 创建一个线程
    void KILL(); // 将标志位设置为false, 退出线程

signals:

public slots:

private:
    // 设置标志位，判断线程是否正在执行
    bool isRun;
};

#endif // MYTHREAD_HPP
