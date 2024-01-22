#include "fish.h"
#include <QtMath>

int Fish::getMoveSteps()
{
    return moveSteps;
}

void Fish::setX(float x)
{
    this->x = x;
}

void Fish::setY(float y)
{
    this->y = y;
}

void Fish::setAnimation(FishAnimation *animation)
{
    this->animation = animation;
}

float Fish::getSpeed()
{
    return speed;
}

Fish::Fish(FishAnimation *animation, int x, int y, int minStay, int maxStay)
{
    this->animation = animation;
    this->x = x;
    this->y = y;
    minStaySteps = minStay;
    maxStaySteps = maxStay;
}

void Fish::nextStep()
{
    if(moveSteps)
    {
        x += moveX;
        y += moveY;
        moveSteps--;
    }
    else
    {
        if(!staySteps)
        {
            staySteps = rand() % (maxStaySteps - minStaySteps + 1) + minStaySteps;
        }
        else
        {
            staySteps--;
        }
    }


    if(currentFrame == animation->frames.size() - 1)
    {
        currentFrame = 0;
    }
    else
    {
        currentFrame++;
    }
}

void Fish::moveTo(int x, int y)
{
    double distance = sqrt(pow(this->x - x, 2) + pow(this->y - y,2));
    staySteps = 0;
    moveSteps = distance / speed;
    moveX = (x - this->x) / (float)moveSteps;
    moveY = (y - this->y) / (float)moveSteps;
}

void Fish::setPosition(int x, int y)
{
    moveSteps = 0;
    this->x = x;
    this->y = y;
}

void Fish::draw(QPainter *painter)
{
    painter->drawImage( x - animation->frames[currentFrame].width() / 2,
                        y - animation->frames[currentFrame].height() / 2,
                       (moveX < 0 ? animation->frames[currentFrame] :  animation->frames[currentFrame].mirrored(true, false)));
}

bool Fish::isMoving()
{
   return moveSteps | staySteps;
}

float Fish::getX()
{
    return x;
}

float Fish::getY()
{
    return y;
}

float Fish::getMoveX()
{
    return moveX;
}

float Fish::getMoveY()
{
    return moveY;
}

AbstractFishDecorator::AbstractFishDecorator(Fish *base) : Fish(base->animation)
{
    this->base = base;
}

int AbstractFishDecorator::getMoveSteps()
{
    return base->getMoveSteps();
}

float AbstractFishDecorator::getX()
{
    return base->getX();
}

float AbstractFishDecorator::getY()
{
    return base->getY();
}

float AbstractFishDecorator::getMoveX()
{
    return base->getMoveX();
}

float AbstractFishDecorator::getMoveY()
{
    return base->getMoveY();
}

bool AbstractFishDecorator::isMoving()
{
    return base->isMoving();
}

void AbstractFishDecorator::draw(QPainter *painter)
{
    base->draw(painter);
}

float AbstractFishDecorator::getSpeed()
{
    return base->getSpeed();
}

void AbstractFishDecorator::setX(float x)
{
    base->setX(x);
}

void AbstractFishDecorator::setY(float y)
{
    base->setY(y);
}

void AbstractFishDecorator::setPosition(int x, int y)
{
    base->setPosition(x, y);
}

void AbstractFishDecorator::setAnimation(FishAnimation *animation)
{
    base->setAnimation(animation);
}

Fish *AbstractFishDecorator::getBase()
{
    return base;
}


void SinusoidFishDecorator::nextStep()
{
    if(base->getMoveSteps())
    {
        base->nextStep();
        base->setY(base->getY() + qCos(base->getMoveSteps() * multiply) * amplitude);
    }

}

void SinusoidFishDecorator::moveTo(int x, int y)
{
    base->moveTo(x, y);
    multiply = 6*M_PI/(float)base->getMoveSteps();
    amplitude = base->getMoveY();
}

QString SinusoidFishDecoratorFactory::getName()
{
    return "Sinusoid";
}

void AccelirationFishDecorator::nextStep()
{
    if(base->getMoveSteps())
    {
        base->nextStep();
        if(base->getMoveSteps() == turnPoint * (turnRatio - 1))
        {
            accelirationX = -((base->getMoveX() * initialMultiply * turnPoint) / (pow(turnPoint * (turnRatio - 1),2)));
            accelirationY = -((base->getMoveY() * initialMultiply * turnPoint) / (pow(turnPoint * (turnRatio - 1),2)));
        }
        moveX += accelirationX;
        moveY += accelirationY;
        base->setX(base->getX() + moveX);
        base->setY(base->getY() + moveY);
    }
}

void AccelirationFishDecorator::moveTo(int x, int y)
{
    base->moveTo(x, y);
    moveX = base->getMoveX() * initialMultiply;
    moveY = base->getMoveY() * initialMultiply;
    turnPoint = base->getMoveSteps() / turnRatio;
    accelirationX = -moveX / turnPoint;
    accelirationY = -moveY / turnPoint;
}

QString AccelirationFishDecoratorFactory::getName()
{
    return "Acceliration";
}

void CurveFishDecorator::nextStep()
{
    if(base->getMoveSteps())
    {
        base->nextStep();
        if(base->getMoveSteps() == turnPoint * (turnRatio - 1))
        {
            acceliration = -((base->getMoveY() * initialMultiply * turnPoint) / (pow(turnPoint * (turnRatio - 1),2)));
        }
        move += acceliration;
        base->setY(base->getY() + move);
    }
}

void CurveFishDecorator::moveTo(int x, int y)
{
    base->moveTo(x, y);
    move = base->getMoveY() * initialMultiply;
    turnPoint = base->getMoveSteps() / turnRatio;
    acceliration = -move / turnPoint;
}

QString CurveFishDecoratorFactory::getName()
{
    return "Curve";
}

AbstractFishDecorator *SinusoidFishDecoratorFactory::getDecorator(Fish *fish)
{
    return new SinusoidFishDecorator(fish);
}

AbstractFishDecorator *AccelirationFishDecoratorFactory::getDecorator(Fish *fish)
{
    return new AccelirationFishDecorator(fish);
}

AbstractFishDecorator *CurveFishDecoratorFactory::getDecorator(Fish *fish)
{
    return new CurveFishDecorator(fish);
}

QString AbstractFishDecoratorFactory::getName()
{
    return "";
}
