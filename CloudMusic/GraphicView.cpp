#include "GraphicView.hpp"
#include <QGraphicsView>
#include <QResizeEvent>
#include <QDebug>

GraphicView::GraphicView(QWidget *parent) : QGraphicsView(parent),
    scene(new QGraphicsScene(this)),
    diskItem(new DiskItem(this)),
    diskPointItem(new DiskPointItem(this))
{
    musicImage.load(":/new/prefix1/Image/disk.png");
    musicImage = musicImage.scaled(QSize(260, 260), Qt::IgnoreAspectRatio);

    scene->addItem(diskItem);
    // 在场景中添加唱针图元
    scene->addItem(diskPointItem);
    setScene(scene);
}

void GraphicView::startNeedleAnimation()
{
    diskPointItem->startNeedleAnimation();
}

void GraphicView::pauseNeedleAnimation()
{
    diskPointItem->pauseNeedleAnimation();
}

void GraphicView::startAnimation()
{
    diskItem->startAnimation();
}

void GraphicView::pauseAnimation()
{
    diskItem->pauseAnimation();
}

QImage GraphicView::makeARGB32Image(QImage image)
{
    QImage circle(":/new/prefix1/Image/circleMask.png");

    image = image.scaled(circle.size(), Qt::KeepAspectRatio);

    QImage fixedImage(circle.size(), QImage::Format_ARGB32_Premultiplied);
    QPainter painter(&fixedImage);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(fixedImage.rect(), Qt::transparent);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    painter.drawImage(0, 0, image);
    painter.end();

    return fixedImage;
}

QImage GraphicView::makeCircleImage(QImage argb32Image)
{
    QImage circle(":/new/prefix1/Image/circleMask.png");

    QPainter painter(&circle);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.drawImage(0, 0, argb32Image);
    painter.end();
    return circle;
}

QImage GraphicView::makeDiskImage(QImage circleImage)
{
    QImage disk(":/new/prefix1/Image/disk.png");

    // 设置以哪张图片为画布
    QPainter painter(&disk);
    // 双线性插值算法
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    // 设置叠加模式
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    // 画图
    painter.drawImage(QPoint((disk.width() - circleImage.width()) / 2.0,
                             (disk.height() - circleImage.height()) / 2.0), circleImage);
    // 2.0 int 转 float 去白边
    painter.end();
    return disk;
}

void GraphicView::resizeEvent(QResizeEvent *resize)
{
    // 以下注释的w, h是动态坐标
    // qreal w = resize->size().width();
    // qreal h = resize->size().height();
    // qDebug() << w << ' ' << h;
    qreal w = 238;
    qreal h = 260;

    scene->setSceneRect(-w/2.0, -h/2.0, w, h);
    // 设置唱针的图层位置
    diskPointItem->setPos(-w/4.2, -h/2.2);
    QGraphicsView::resizeEvent(resize);
}

void GraphicView::setMusicImage(const QImage &image)
{
    musicImage = image;

    QImage argb32Img = makeARGB32Image(image);
    // argb32Img.save("2.png");
    QImage circleImg = makeCircleImage(argb32Img);
    // circleImg.save("3.png");
    QImage diskImg = makeDiskImage(circleImg);
    diskImg = diskImg.scaled(QSize(260, 260), Qt::IgnoreAspectRatio);

    diskItem->setImage(diskImg);

    update();
}

void GraphicView::paintEvent(QPaintEvent *painEvent)
{
/*
    QPainter painter(viewport()); // 获得当前的对象
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.drawImage(rect(), musicImage);
*/

    QGraphicsView::paintEvent(painEvent);
}
