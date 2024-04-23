#include "toxicmushroom.h"
#include "mainwindow.h"
#include "floorbricks.h"
#include "mario.h"
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QList>
#include <typeinfo>

toxicmushroom::toxicmushroom(QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{

    setPos(1000,400);
    setPixmap(QPixmap(":/new/prefix1/image/toxic mushroom1.png"));


    QTimer*timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(toxicmushroom_move()));
    connect(timer, SIGNAL(timeout()), this, SLOT(animation()));
    connect(timer, SIGNAL(timeout()), this, SLOT(countY()));
    connect(timer, SIGNAL(timeout()), this, SLOT(gravity()));
    connect(timer, SIGNAL(timeout()), this, SLOT(colliedWithBrick()));
    timer->start(10);

}

void toxicmushroom::toxicmushroom_move(){
    if(faceLeft){
        if(x()==0){
            faceLeft = false;
            setPixmap(QPixmap(":/new/prefix1/image/toxic mushroom2.png"));
        }
        else setPos(x()-2,y());
    }
    else if(!faceLeft){
        if(x()==7000){
            faceLeft = true;
            setPixmap(QPixmap(":/new/prefix1/image/toxic mushroom1.png"));
        }
        else setPos(x()+2,y());
    }
}

void toxicmushroom::gravity(){

         //collidedBottom = false;
     if(!collidedBottom){
         double acceleration = 0.08; // 加速度
         velocity += acceleration;
         //qDebug() << y();
     }
}

void toxicmushroom::countY(){
    if(((collidedBottom)&&(velocity>=0))||(collidedTop)){   //如果y==450且VC>=0則將速度和位置歸零
        collidedBottom = true;
        velocity = 0;
        qDebug() << "velocity:" << velocity;
        qDebug() << "countY:collideBottom:" << collidedBottom << "; collideTop:" <<collidedTop;
    }
    setPos(x(), y()+ velocity);
    qDebug() << "Y = " << y()-velocity << "+" << velocity;
}


void toxicmushroom::colliedWithBrick()
{
    collidedBottom = false;
    collidedLeft = false;
    collidedLeft = false;
    collidedTop = false;
    QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
    for(int i =0;i<collidingItems.size();i++){
        QGraphicsItem *item = collidingItems[i];
        if(typeid(*item) == typeid(floorBricks)){
            qDebug() << "collided floor brick";
            qDebug() << "size: x from" << item->x()-25 << " to " << item->x()+25 << ";y from" << item->y()-50 << " to " << item->y()+50;
            qDebug() << "toxicmushroom x" <<x()<<" y "<<y();
            if((item->y()+75 >= y()) && (x() < item->x()+25) && (x() > item->x()-25))
                collidedTop = true;
            if((item->y()-75 <= y()) && (x() < item->x()+25) && (x() > item->x()-25))
                collidedBottom = true;
            if((item->x()-25 >= x()) && (y() > item->y()-49) && (y() < item->y()+49))
                collidedRight = true;
            if((item->x()+25 <= x()) && (y() > item->y()-49) && (y() < item->y()+49))
                collidedLeft = true;

            }
    }
}
