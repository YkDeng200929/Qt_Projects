#ifndef B_HPP
#define B_HPP

#include <QObject>

class B : public QObject
{
    Q_OBJECT
public:
    explicit B(QObject *parent = nullptr);

signals:
    void sig_BSignal(QString qstr);

public slots:
    void slot_BSlot(QString qstr);
};

#endif // B_HPP
