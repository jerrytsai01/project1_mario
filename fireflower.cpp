#include "fireflower.h"
#include "mario.h"
#include "mainwindow.h"
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QList>

fireflower::fireflower(int x,int y,QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent),x(x),y(y)
{
    setPixmap(QPixmap(":/new/prefix1/image/item/Fire Flower.png"));
    setPos(x,y);
    QTimer*timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(flower_eaten_by_mario()));
    timer->start(10);
}

void fireflower::flower_eaten_by_mario(){
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



