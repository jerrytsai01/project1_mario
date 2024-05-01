
#include "supermushroom.h"
#include "mainwindow.h"
#include "mario.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QList>

supermushroom::supermushroom(QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{
    setPixmap(QPixmap(":/new/prefix1/image/item/super mushroom.png"));
    setPos(250,400);
    QTimer*timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(supermushroom_move()));
    connect(timer, SIGNAL(timeout()), this, SLOT(eaten_by_mario()));
    timer->start(10);
}

//超級蘑菇向左移動
void supermushroom::supermushroom_move(){
    //setPos(x()-1,y());
}

//被馬力歐吃
void supermushroom::eaten_by_mario(){
    QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
    for(int i =0;i<collidingItems.size();i++){
        QGraphicsItem *item = collidingItems[i];
        if(typeid(*item) == typeid(mario)){
            scene()->removeItem(this);
            delete this;
            qDebug() << "supermushroom is eaten by mario";
        }
    }
}
