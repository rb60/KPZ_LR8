#ifndef ANIMATIONPREVIEW_H
#define ANIMATIONPREVIEW_H

#include <QWidget>
#include <QPaintEvent>
#include "fish.h"

class animationPreview : public QWidget
{
    Q_OBJECT
public:
    explicit animationPreview(QWidget *parent = nullptr);
    void setAnimation(FishAnimation* animation);
private:
    FishAnimation* animation = nullptr;
    virtual void paintEvent(QPaintEvent* pe);
    virtual void timerEvent(QTimerEvent*);
    int currentFrame = 0;
signals:

};

#endif // ANIMATIONPREVIEW_H
