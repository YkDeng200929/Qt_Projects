#ifndef GRAPHICVIEW_HPP
#define GRAPHICVIEW_HPP

#include <QGraphicsView>
#include <QImage>
#include "DiskItem.hpp"
#include "DiskPointItem.hpp"
#include <QGraphicsScene>

class GraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphicView(QWidget *parent = nullptr);

    void startNeedleAnimation();
    void pauseNeedleAnimation();
    void startAnimation();
    void pauseAnimation();
    // 将组合好的专辑唱片图片设置到场景中(设置图元)
    void setMusicImage(const QImage &image);

    // 将得到的专辑封面图片转换成Argb32格式用于与唱片圆形叠加
    QImage makeARGB32Image(QImage image);
    // 将专辑封面叠加成一个小圆
    QImage makeCircleImage(QImage argb32Image);
    // 将小圆专辑封面与唱片组合在一起
    QImage makeDiskImage(QImage circleImage);


protected:
    void resizeEvent(QResizeEvent *resize);
    void paintEvent(QPaintEvent *painEvent);

signals:

public slots:

private:
    QImage musicImage;
    QGraphicsScene *scene;
    DiskItem *diskItem;
    DiskPointItem *diskPointItem;
};

#endif // GRAPHICVIEW_HPP
