#ifndef DISKITEM_HPP
#define DISKITEM_HPP

#include <QObject>
#include <QGraphicsItem>
#include <QImage>
#include <QPropertyAnimation>

class DiskItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
    Q_PROPERTY(qreal anagle READ rotation WRITE setRotation)
public:
    explicit DiskItem(QObject *parent = nullptr);

    void setImage(const QImage &musicImage);
    void startAnimation();
    void pauseAnimation();

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

signals:

public slots:

private:
    QPropertyAnimation *animation;
    QImage image;
};

#endif // DISKITEM_HPP
