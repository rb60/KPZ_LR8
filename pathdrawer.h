#ifndef PATHDRAWER_H
#define PATHDRAWER_H

#include <QWidget>
#include <QImage>
#include "fish.h"

class pathDrawer : public QWidget
{
    Q_OBJECT
public:
    explicit pathDrawer(QWidget *parent = nullptr);
    void setFish(Fish* fish);
    virtual void paintEvent(QPaintEvent* pe);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void timerEvent(QTimerEvent*);
    Fish* fish = nullptr;
    void restart();
private:
    QImage* img;
    int offset = 70;
    int xEnd;
    int yEnd;

signals:

};

#endif // PATHDRAWER_H
