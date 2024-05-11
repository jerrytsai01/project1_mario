#include "toxicmushroom.h"
#include "mainwindow.h"
#include "floorbricks.h"
#include "bullet.h"
#include "mario.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QList>

toxicmushroom::toxicmushroom(int x,int y,QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent),x(x),y(y)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);

    setPos(x,y);
    setPixmap(QPixmap(":/new/prefix1/image/toxic mushroom1.png"));

    QTimer*timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(toxicmushroom_move()));
    connect(timer, SIGNAL(timeout()), this, SLOT(animation()));
    connect(timer, SIGNAL(timeout()), this, SLOT(countY()));
    connect(timer, SIGNAL(timeout()), this, SLOT(gravity()));
    connect(timer, SIGNAL(timeout()), this, SLOT(colliedWithBrick()));
    connect(timer, SIGNAL(timeout()), this, SLOT(colliedWithMario()));
    connect(timer, SIGNAL(timeout()), this, SLOT(hitByBullet()));
    connect(timer, SIGNAL(timeout()), this, SLOT(livecheck()));
    timer->start(10);
}

//移動
void toxicmushroom::toxicmushroom_move(){
    if(faceLeft){
        if(x==700) faceLeft = false;
        else setPos(x-1,y);
    }
    else if(!faceLeft){
        if(x==1400) faceLeft = true;
        else setPos(x+1,y);
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

//走路動畫
void toxicmushroom::animation(){
    timer++;
    if(timer % 30 < 15) setPixmap(QPixmap(":/new/prefix1/image/toxic mushroom2.png"));
    else setPixmap(QPixmap(":/new/prefix1/image/toxic mushroom1.png"));
}

void toxicmushroom::countY(){
    if(((collidedBottom)&&(velocity>=0))||(collidedTop)){   //如果y==450且VC>=0則將速度和位置歸零
        collidedBottom = true;
        velocity = 0;
        //qDebug() << "velocity:" << velocity;
        //qDebug() << "countY:collideBottom:" << collidedBottom << "; collideTop:" <<collidedTop;
    }
    setPos(x, y+ velocity);
    //qDebug() << "Y = " << y()-velocity << "+" << velocity;
}

//被馬力歐踩死
void toxicmushroom::colliedWithMario(){
    QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
    for(int i =0;i<collidingItems.size();i++){
        QGraphicsItem *item = collidingItems[i];
        if(typeid(*item) == typeid(mario)){
            //qDebug() << "collided mario";
            //qDebug() << "size: x from" << item->x()-25 << " to " << item->x()+25 << ";y from" << item->y()-50 << " to " << item->y()+50;
            //qDebug() << "toxicmushroom x" <<x()<<" y "<<y();
            //if(MainWindow::player.small == true)
            if(y-45 >= item->y() and (item->x() >= x-50) and (item->x() <= x+50)){
                live = false;
            }
        }
    }
}

//被子彈打到
void toxicmushroom::hitByBullet(){
    QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
    for(int i =0;i<collidingItems.size();i++){
        QGraphicsItem *item = collidingItems[i];
        if(typeid(*item) == typeid(bullet)){
            qDebug() << "hit by bullet";
            qDebug() << "toxicmushroom x" <<x<<" y "<<y;
            live = false;
            qDebug() << "Toxicmushroom is killed by bullet";
        }
    }
}

void toxicmushroom::colliedWithBrick(){
    collidedBottom = false;
    collidedLeft = false;
    collidedRight = false;
    collidedTop = false;
    QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
    for(int i =0;i<collidingItems.size();i++){
        QGraphicsItem *item = collidingItems[i];
        if(typeid(*item) == typeid(floorBricks)){
            //qDebug() << "collided floor brick";
            //qDebug() << "size: x from" << item->x()-25 << " to " << item->x()+25 << ";y from" << item->y()-50 << " to " << item->y()+50;
            //qDebug() << "toxicmushroom x" <<x()<<" y "<<y();
            if((item->y()+75 >= y) && (x < item->x()+25) && (x > item->x()-25))
                collidedTop = true;
            if((item->y()-75 <= y) && (x < item->x()+25) && (x > item->x()-25))
                collidedBottom = true;
            if((item->x()-25 <= x) && (y > item->y()-48) && (y < item->y()+48))
                collidedRight = true;
            if((item->x()+25 >= x) && (y > item->y()-48) && (y < item->y()+48))
                collidedLeft = true;
        }
    }
}


//確認有無存活
void toxicmushroom::livecheck(){
    if(!live){
        setPixmap(QPixmap(":/new/prefix1/image/toxic mushroom3.png"));
        qDebug() << "Toxicmushroom is killed by Mario";
        deathTimer ++;
        if(deathTimer >= 10){
            scene()->removeItem(this);
            delete this;
            qDebug() << "toxicmushroom deleted" ;
        }
    }
}
