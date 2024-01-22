#include "animationpreview.h"

animationPreview::animationPreview( QWidget *parent)
    : QWidget{parent}
{
    startTimer(50);
}

void animationPreview::setAnimation(FishAnimation *animation)
{
    this->animation = animation;
}

void animationPreview::paintEvent(QPaintEvent *pe)
{
    QPainter* painter = new QPainter(this);
    painter->drawImage(0,0, animation->frames[currentFrame].scaled(this->width(), this->height(), Qt::KeepAspectRatio));
}

void animationPreview::timerEvent(QTimerEvent *)
{
    if (animation != nullptr)
    {
        if(currentFrame == animation->frames.size() - 1)
        {
            currentFrame = 0;
        }
        else
        {
            currentFrame++;
        }
        update();
    }

}




