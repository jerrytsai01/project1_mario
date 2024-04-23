#include "toxicmushroom.h"
#include "mainwindow.h"
#include "floorbricks.h"
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QList>
#include <typeinfo>

toxicmushroom::toxicmushroom(QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{

    //初始位置跟圖片
    setPos(1000,450);
    setPixmap(QPixmap(":/new/prefix1/image/toxic mushroom1.png"));

    //持續偵測的計時
    QTimer*timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(toxicmushroom_move()));
    timer->start(10);
}

 void toxicmushroom::toxicmushroom_move(){
    setPos(x()-2,y());
}

