#include "supermushroom.h"
#include "mainwindow.h"
#include "mario.h"
#include "floorbricks.h"
#include "stonebricks.h"
#include "waterpipe.h"
#include "normalbricks.h"
#include "boxbricks.h"
#include "brokenbricks.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QList>

supermushroom::supermushroom(int X,int Y,QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{
    setPixmap(QPixmap(":/new/prefix1/image/item/super mushroom.png"));
    setPos(X,Y);
    QTimer*timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(supermushroom_move()));
    connect(timer, SIGNAL(timeout()), this, SLOT(eaten_by_mario()));
    connect(timer, SIGNAL(timeout()), this, SLOT(gravity()));
    connect(timer, SIGNAL(timeout()), this, SLOT(countY()));
    connect(timer, SIGNAL(timeout()), this, SLOT(collidedWithBrick()));
    timer->start(10);
}

void supermushroom::supermushroom_move(){
    qDebug()<<"move";
    if(faceRight){
        setPos(x()+1, y());
    }
    else{
        setPos(x()-1, y());
    }
}

//被馬力歐吃
void supermushroom::eaten_by_mario(){
    QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
    for(int i =0;i<collidingItems.size();i++){
        QGraphicsItem *item = collidingItems[i];
        if(typeid(*item) == typeid(mario)){
            Deathtime++;
            if(Deathtime>3){
                scene()->removeItem(this);
                delete this;
                qDebug() << "supermushroom is eaten by mario";
            }
        }
    }
}

void supermushroom::gravity(){
    if(!collidedBottom){
        double acceleration;
        acceleration = 0.15;
        Vg += acceleration;
        //qDebug() << y();
    }
}

void supermushroom::countY(){
    if(((collidedBottom)&&(Vg>=0))||((collidedTop)&&(Vg<0))){
        collidedBottom = true;
        Vg = 0;
    }
    setPos(x(), y()+Vg);
}

void supermushroom::collidedWithBrick(){
    collidedBottom = false;
    collidedRight = false;
    collidedLeft = false;
    collidedTop = false;
    QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
    for(int i =0;i<collidingItems.size();i++){
        QGraphicsItem *item = collidingItems[i];
        if(typeid(*item) == typeid(floorBricks)){
            if((item->y() > y()) && (x() < item->x()+26) && (x() > item->x()-26)){
                Vg = 0;
                collidedBottom = true;
                //qDebug() << "1";
            }
            else if((item->x() > x()) && (y() > item->y()-48) && (y() < item->y()+48)){
                //qDebug() << "111111111111111";
                qDebug() << "CR";
                collidedRight = true;
                faceRight = false;
                //qDebug() << "2";
            }
            else if((item->x() < x()) && (y() > item->y()-48) && (y() < item->y()+48)){
                qDebug() << "CL";
                collidedLeft = true;
                faceRight = true;
                //qDebug() << "3";
            }
        }
        if(typeid(*item) == typeid(waterpipe)){
            if((item->y() > y()) && (x() < item->x()) && (x() > item->x()-100)){
                Vg = 0;
                collidedBottom = true;
            }
            else if((item->x() > x()) && (y() > item->y()) && (y() < item->y()+100)){
                qDebug() << "111111111111111";
                collidedRight = true;
                faceRight = false;
            }
            else if((item->x() < x()) && (y() > item->y()) && (y() < item->y()+100)){
                collidedLeft = true;
                faceRight = true;
            }
        }
        if((typeid(*item) == typeid(stonebricks)) || (typeid(*item) == typeid(normalbricks)) || (typeid(*item) == typeid(boxbricks)) || (typeid(*item) == typeid(brokenbricks))){
            //(item->y() < y()) && (x() < item->x()+45) && (x() > item->x()-40)
            if((item->y() > y()) && (x() < item->x()+45) && (x() > item->x()-45)){
                Vg = 0;
                collidedBottom = true;
            }
            else if((item->x() - 50 >= x()) && (y() + 45 > item->y()) && (y() < item->y() + 45)){
                qDebug() << "CR";
                collidedRight = true;
                faceRight = false;
            }
            else if((item->x() < x()) && (y() + 45 > item->y()) && (y() < item->y() + 45)){
                qDebug() << "CL";
                collidedLeft = true;
                faceRight = true;
            }
        }
    }
}

