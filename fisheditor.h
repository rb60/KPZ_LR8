#ifndef FISHEDITOR_H
#define FISHEDITOR_H

#include <QDialog>
#include <QVector>
#include <QListWidgetItem>
#include "fish.h"

namespace Ui {
class FishEditor;
}

class FishEditor : public QDialog
{
    Q_OBJECT

public:
    explicit FishEditor(QVector<FishAnimation*> animations, QVector<AbstractFishDecoratorFactory*> decorators, QWidget *parent = nullptr);
    void showEvent(QShowEvent *event) override;
    Fish* getFish();
    void clearFish();
    void deleteFish();
    ~FishEditor();
public slots:
    void selectAnimation(QListWidgetItem *item);
    void addDecorator();
    void removeDecorator();

private:
    QVector<FishAnimation*> animations;
    QVector<AbstractFishDecoratorFactory*> decorators;
    Fish* fish;
    int decoratorCount = 0;
    Ui::FishEditor *ui;
};

#endif // FISHEDITOR_H
