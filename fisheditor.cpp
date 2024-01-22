#include "fisheditor.h"
#include "ui_fisheditor.h"
#include <QList>
#include <QMenuBar>

FishEditor::FishEditor(QVector<FishAnimation*> animations, QVector<AbstractFishDecoratorFactory*> decorators, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FishEditor)
{
    ui->setupUi(this);
    this->animations = animations;
    this->decorators = decorators;
    for (int i = 0; i < animations.size(); i++)
    {
        ui->AnimationList->addItem(QString::number(i));
    }
    for (int i = 0; i < decorators.size(); i++)
    {
        ui->DecoratorList->addItem(decorators[i]->getName());
    }
    connect(ui->AnimationList, SIGNAL(itemClicked(QListWidgetItem*)), SLOT(selectAnimation(QListWidgetItem*)));
    connect(ui->addButton, SIGNAL(clicked()), SLOT(addDecorator()));
    connect(ui->RemoveButton, SIGNAL(clicked()), SLOT(removeDecorator()));

    QMenuBar* menu = new QMenuBar(this);
    menu->addAction("Add", this, SLOT(accept()));
    menu->addAction("Canel", this, SLOT(reject()));
    this->layout()->setMenuBar(menu);
}

void FishEditor::showEvent(QShowEvent *event)
{
    fish = new Fish(animations[0]);
    ui->PathDrawer->setFish(fish);
    ui->AnimationPreview->setAnimation(animations[0]);
    ui->AnimationList->setCurrentRow(0);
    ui->DecoratorList->setCurrentRow(0);
}

Fish *FishEditor::getFish()
{
    return fish;
}

void FishEditor::clearFish()
{
    ui->PathDrawer->setFish(nullptr);
    fish = nullptr;
}

void FishEditor::deleteFish()
{
    ui->PathDrawer->setFish(nullptr);
    delete fish;
}

FishEditor::~FishEditor()
{
    delete ui;
}

void FishEditor::selectAnimation(QListWidgetItem *item)
{
    ui->AnimationPreview->setAnimation(animations[ui->AnimationList->row(item)]);
    fish->setAnimation(animations[ui->AnimationList->row(item)]);
}

void FishEditor::addDecorator()
{
    QList<QListWidgetItem*> selected = ui->DecoratorList->selectedItems();
    if(selected.size() != 0)
    {
        fish = decorators[ui->DecoratorList->row(selected[0])]->getDecorator(fish);
        ui->PathDrawer->setFish(fish);
        ui->PathDrawer->restart();
        decoratorCount++;
    }
}

void FishEditor::removeDecorator()
{
    if(decoratorCount > 0)
    {
        Fish* temp = fish;
        fish = ((AbstractFishDecorator*)fish)->getBase();
        ui->PathDrawer->setFish(fish);
        ui->PathDrawer->restart();
        delete temp;
        decoratorCount--;
    }
}
