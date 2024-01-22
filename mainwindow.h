#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fish.h"
#include "fisheditor.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent* pe);
    virtual void timerEvent(QTimerEvent*);
    ~MainWindow();
    int count = 0;
public slots:
    void openFishEditor();
private:
    FishEditor* editor;
    QVector<Fish*> fishes;
    QVector<FishAnimation*> animations;
    QVector<AbstractFishDecoratorFactory*> decorators;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
