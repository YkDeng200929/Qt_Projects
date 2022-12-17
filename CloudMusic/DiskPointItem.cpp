#include "DiskPointItem.hpp"
#include <QPainter>
#include <QMediaPlayer>

DiskPointItem::DiskPointItem(QObject *parent) : QObject(parent),
    animation(new QPropertyAnimation(this, "anagle", this))
{
    image.load(":/new/prefix1/Image/magnetNeedle.png");
    image = image.scaled(QSize(135, 33), Qt::IgnoreAspectRatio);
    qreal x = image.size().width();
    // 设置旋转点坐标
    setTransformOriginPoint(-x/2.5, 0);
    animation->setDuration(100);
    animation->setLoopCount(1);
}

void DiskPointItem::startNeedleAnimation()
{
    animation->setStartValue(0);
    animation->setEndValue(10);
    animation->start();
}

void DiskPointItem::pauseNeedleAnimation()
{
    animation->setStartValue(10);
    animation->setEndValue(0);
    animation->start();
}

QRectF DiskPointItem::boundingRect() const
{
    // 设置唱针的坐标点位置
    // return QRectF(-(image.width()), -(4*(image.height())), image.width(), image.height());
    return QRectF(-(image.width())/2.0, -(image.height())/2.0, image.width(), image.height());
}

void DiskPointItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(), image);
}
