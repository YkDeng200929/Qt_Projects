#include "DiskItem.hpp"
#include <QPainter>
#include <QMediaPlayer>

DiskItem::DiskItem(QObject *parent) : QObject(parent),
    animation(new QPropertyAnimation(this, "anagle", this))
    // 上面还得加上个this，否则会内存泄露
{
    image.load(":/new/prefix1/Image/disk.png");
    image = image.scaled(QSize(260, 260), Qt::IgnoreAspectRatio);
    animation->setDuration(25000);
    animation->setStartValue(0);
    animation->setEndValue(360);
    animation->setLoopCount(-1);
}

void DiskItem::setImage(const QImage &musicImage)
{
    image = musicImage;

    update();
}

void DiskItem::startAnimation()
{
    animation->start();
}

void DiskItem::pauseAnimation()
{
    animation->pause();
}

QRectF DiskItem::boundingRect() const
{
    // 设置场景大小
    return QRectF(image.width() / -2.0, image.height() / -2.0, image.width(), image.height());
}

void DiskItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawImage(boundingRect(), image);
}
