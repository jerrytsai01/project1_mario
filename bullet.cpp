#include "bullet.h"
#include "fireflower.h"
#include "mario.h"
#include "toxicmushroom.h"
#include "mainwindow.h"
#include "waterpipe.h"
#include "stonebricks.h"
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QList>

bullet::bullet(QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{
    setPixmap(QPixmap(":/new/prefix1/image/bullet.png"));
    QTimer*timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(shot_by_mario()));
    connect(timer, SIGNAL(timeout()), this, SLOT(hit_the_toxicmushroom()));
    connect(timer, SIGNAL(timeout()), this, SLOT(hit_the_bricks()));
    timer->start(10);
}

void bullet::shot_by_mario(bool faceRight){
    if(faceRight)
        setPos(x()+3, y());
    else
        setPos(x()-3, y());
}

void bullet::hit_the_toxicmushroom(){
    QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
    for(int i =0;i<collidingItems.size();i++){
        QGraphicsItem *item = collidingItems[i];
        if(typeid(*item) == typeid(toxicmushroom)){
            scene()->removeItem(this);
            delete this;
            qDebug() << "bullet hit the toxicmushroom";
        }
    }
}

void bullet::hit_the_bricks(){
    QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
    for(int i =0;i<collidingItems.size();i++){
        QGraphicsItem *item = collidingItems[i];
        if(typeid(*item) == typeid(stonebricks) || typeid(*item) == typeid(waterpipe)){
            scene()->removeItem(this);
            delete this;
            qDebug() << "bullet hit an obstacle";
        }
    }
}
