#include "bullet.h"
#include "fireflower.h"
#include "mario.h"
#include "toxicmushroom.h"
#include "mainwindow.h"
#include "waterpipe.h"
#include "stonebricks.h"
#include "coin.h"
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QList>
#include <QtMath>

bullet::bullet(QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{
    setPixmap(QPixmap(":/new/prefix1/image/bullet.png"));
    speed = 10;
    QTimer*timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(shot_by_mario()));
    connect(timer, SIGNAL(timeout()), this, SLOT(hit_the_toxicmushroom()));
    connect(timer, SIGNAL(timeout()), this, SLOT(hit_the_bricks()));
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(10);
}

void bullet::setTargetPosition(const QPointF &target, const QPointF &start)
{
    // Calculate the angle between the start position and the target position
    angle = qAtan2(target.y()-start.y(), target.x()-start.x());
    setPos(start);
}

void bullet::move()
{
    qreal dx = speed*qCos(angle);
    qreal dy = speed*qSin(angle);
    QPointF newPos = pos() + QPointF(dx, dy);
    // Set the new position of the bullet
    setPos(newPos);


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
        if(typeid(*item) == typeid(mario) or typeid(*item) == typeid(QGraphicsPixmapItem) or typeid(*item) == typeid(Coin)){
            continue;
            qDebug() << "fff";
        }
        else{
            scene()->removeItem(this);
            delete this;
            qDebug() << "bullet collide with " << item;
            break;
        }
    }
    /*
    for(int i =0;i<collidingItems.size();i++){
        QGraphicsItem *item = collidingItems[i];
        if(typeid(*item) == typeid(stonebricks) || typeid(*item) == typeid(waterpipe)){
            scene()->removeItem(this);
            delete this;
            qDebug() << "bullet hit an obstacle";
        }
    }
    */
}


