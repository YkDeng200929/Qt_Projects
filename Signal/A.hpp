#ifndef A_HPP
#define A_HPP

#include <QObject>

class A : public QObject
{
    Q_OBJECT
public:
    explicit A(QObject *parent = nullptr);

signals:
    void sig_ASignal(QString qstr);

public slots:
    void slot_ASlot(QString qstr);
};

#endif // A_HPP
