#ifndef DISKPOINTITEM_HPP
#define DISKPOINTITEM_HPP

#include <QObject>
#include <QGraphicsItem>
#include <QImage>
#include <QPropertyAnimation>

class DiskPointItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
    Q_PROPERTY(qreal anagle READ rotation WRITE setRotation)
public:
    explicit DiskPointItem(QObject *parent = nullptr);

    void startNeedleAnimation();
    void pauseNeedleAnimation();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

signals:

public slots:

private:
    QPropertyAnimation *animation;
    QImage image;
};

#endif // DISKPOINTITEM_HPP
