#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPaintEvent>
#include "pathdrawer.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    animations.resize(3);
    animations[0] = new FishAnimation;
    animations[0]->frames.append(QImage(":/frames/fish1frame1.png"));
    animations[0]->frames.append(QImage(":/frames/fish1frame2.png"));
    animations[0]->frames.append(QImage(":/frames/fish1frame3.png"));

    animations[1] = new FishAnimation;
    animations[1]->frames.append(QImage(":/frames/fish2frame1.png"));
    animations[1]->frames.append(QImage(":/frames/fish2frame2.png"));
    animations[1]->frames.append(QImage(":/frames/fish2frame3.png"));

    animations[2] = new FishAnimation;
    animations[2]->frames.append(QImage(":/frames/fish3frame1.png"));
    animations[2]->frames.append(QImage(":/frames/fish3frame2.png"));
    animations[2]->frames.append(QImage(":/frames/fish3frame3.png"));

    decorators.resize(3);
    decorators[0] = new SinusoidFishDecoratorFactory;
    decorators[1] = new AccelirationFishDecoratorFactory;
    decorators[2] = new CurveFishDecoratorFactory;

    editor = new FishEditor(animations, decorators, this);

    fishes.resize(count);
    for(int i = 0; i < fishes.size(); i++)
    {
        fishes[i] = new Fish(animations[rand() % 3], rand() % this->width(), rand() % this->height());
    }

    menuBar()->addAction("Add Fish", this, SLOT(openFishEditor()));
    startTimer(50);
}

void MainWindow::paintEvent(QPaintEvent *pe)
{
    QPainter* painter = new QPainter(this);
    painter->fillRect(0, 0, pe->rect().width(), pe->rect().height(), QColor(153, 255, 255));
    for(int i = 0; i < fishes.size(); i++)
    {
        fishes[i]->draw(painter);
    }
    painter->end();
    delete painter;
}

void MainWindow::timerEvent(QTimerEvent *)
{
    for(int i = 0; i < fishes.size(); i++)
    {
        if(!fishes[i]->isMoving() && rand() % 20 < 3)
        {
            fishes[i]->moveTo(rand() % this->width(), rand() % this->height());
        }
        fishes[i]->nextStep();
    }
    update();
}

MainWindow::~MainWindow()
{
    for(int i = 0; i < fishes.size(); i++)
    {
        delete fishes[i];
    }

    for(int i = 0; i < 3; i++)
    {
        delete animations[i];
    }

    for(int i = 0; i < 3; i++)
    {
        delete decorators[i];
    }

    delete ui;
}

void MainWindow::openFishEditor()
{
    if(editor->exec() == QDialog::Accepted)
    {
        fishes.append(editor->getFish());
        editor->clearFish();
        fishes.last()->setPosition(rand() % this->width(), rand() % this->height());
        fishes.last()->moveTo(rand() % this->width(), rand() % this->height());
    }
    else
    {
        editor->deleteFish();
    }
}

