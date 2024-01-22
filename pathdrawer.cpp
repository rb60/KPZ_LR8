#include "pathdrawer.h"
#include <QResizeEvent>

pathDrawer::pathDrawer(QWidget *parent)
    : QWidget{parent}
{
    img = new QImage(100, 100, QImage::Format_RGB32);
    img->fill(Qt::white);
    startTimer(10);
}

void pathDrawer::setFish(Fish *fish)
{
    this->fish = fish;
}

void pathDrawer::paintEvent(QPaintEvent *pe)
{
    QPainter* painter = new QPainter(this);
    painter->drawImage(0,0, *img);
    delete painter;
}

void pathDrawer::resizeEvent(QResizeEvent *event)
{

    *img = img->scaled(event->size());
    xEnd = event->size().width() - offset;
    yEnd = event->size().height() - offset;
    restart();
}

void pathDrawer::timerEvent(QTimerEvent *)
{
    if(fish != nullptr)
    {
        QPainter* imgPainter = new QPainter(img);
        imgPainter->setBrush(QBrush(Qt::black));
        if(!fish->isMoving())
        {
            fish->setPosition(offset, offset);
            fish->moveTo(xEnd, yEnd);
        }
        fish->nextStep();
        imgPainter->fillRect(0, 0, img->width(), img->height(), QColor(255,255,255,15));
        imgPainter->drawEllipse(fish->getX() - fish->getSpeed(),
                                fish->getY() - fish->getSpeed(),
                                fish->getSpeed() * 2,
                                fish->getSpeed() * 2);
        update();
        delete imgPainter;
    }
}

void pathDrawer::restart()
{
    if(fish != nullptr)
    {
        fish->setPosition(offset, offset);
        fish->moveTo(xEnd, yEnd);
    }
    img->fill(Qt::white);
}
