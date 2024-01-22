#ifndef FISH_H
#define FISH_H
#include <QVector>
#include <QImage>
#include <QPainter>


class FishAnimation
{
public:
    QVector<QImage> frames;
};


class Fish
{
private:
    int currentFrame = 0;
    float moveX = 0;
    float moveY = 0;
    int moveSteps = 0;
    float x;
    float y;
    float speed = 3;
    int minStaySteps;
    int maxStaySteps;
    int staySteps = 0;
public:
    FishAnimation* animation;
    Fish(FishAnimation* animation, int x = 0, int y = 0, int minStay = 5, int maxStay = 20);
    virtual float getSpeed();
    virtual void nextStep();
    virtual void moveTo(int x, int y);
    virtual void setPosition(int x, int y);
    virtual void draw(QPainter* painter);
    virtual bool isMoving();
    virtual float getX();
    virtual float getY();
    virtual float getMoveX();
    virtual float getMoveY();
    virtual int getMoveSteps();
    virtual void setX(float x);
    virtual void setY(float y);
    virtual void setAnimation(FishAnimation* animation);
    virtual ~Fish(){}
};

class AbstractFishDecorator : public Fish
{
protected:
    Fish* base;
public:
    AbstractFishDecorator(Fish* base);
    int getMoveSteps() override;
    float getX() override;
    float getY() override;
    float getMoveX() override;
    float getMoveY() override;
    bool isMoving() override;
    void draw(QPainter* painter) override;
    float getSpeed() override;
    void setX(float x) override;
    void setY(float y) override;
    void setPosition(int x, int y) override;
    void setAnimation(FishAnimation* animation) override;
    Fish* getBase();
    ~AbstractFishDecorator() override {}

};

class AbstractFishDecoratorFactory
{
public:
    virtual AbstractFishDecorator* getDecorator(Fish* fish) = 0;
    virtual QString getName();
};





class SinusoidFishDecorator : public AbstractFishDecorator
{
private:
    float multiply;
    float amplitude;
public:
    SinusoidFishDecorator(Fish* base) : AbstractFishDecorator(base){}
    void nextStep() override;
    void moveTo(int x, int y) override;
    ~SinusoidFishDecorator() override {}


};

class SinusoidFishDecoratorFactory : public AbstractFishDecoratorFactory
{
public:
    AbstractFishDecorator* getDecorator(Fish* fish) override;
    QString getName() override;
};




class AccelirationFishDecorator : public AbstractFishDecorator
{
private:
    double moveX = 0;
    double moveY = 0;
    double accelirationX;
    double accelirationY;
    int turnPoint;
    int turnRatio = 4;
    float initialMultiply = 2;
public:
    AccelirationFishDecorator(Fish* base) : AbstractFishDecorator(base){}
    void nextStep() override;
    void moveTo(int x, int y) override;
    ~AccelirationFishDecorator() override {}
};

class AccelirationFishDecoratorFactory : public AbstractFishDecoratorFactory
{
public:
    AbstractFishDecorator* getDecorator(Fish* fish) override;
    QString getName() override;
};


class CurveFishDecorator : public AbstractFishDecorator
{
private:
    double move = 0;
    double acceliration;
    int turnPoint;
    int turnRatio = 3;
    float initialMultiply = 2;
public:
    CurveFishDecorator(Fish* base) : AbstractFishDecorator(base){}
    void nextStep() override;
    void moveTo(int x, int y) override;
    ~CurveFishDecorator() override {}
};

class CurveFishDecoratorFactory : public AbstractFishDecoratorFactory
{
public:
    AbstractFishDecorator* getDecorator(Fish* fish) override;
    QString getName() override;
};



#endif // FISH_H
