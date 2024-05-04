#include "boxbricks.h"
#include "mario.h"
#include"coin.h"
#include "supermushroom.h"
#include "fireflower.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include<QTimer>

boxbricks::boxbricks(int x,int y,int item,QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent),x(x),y(y),item(item)
{
    setPixmap(QPixmap(":/new/prefix1/image/brick/box brick.png"));
    setPos(x,y);

    QTimer *timer =new QTimer(this);
    connect(timer,&QTimer::timeout,this,&boxbricks::touch);
    timer->start(5);
    connect(this, SIGNAL(touched()), this, SLOT(obj()));
}

void boxbricks::touch(){
    QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
    for (int i =0;i<collidingItems.size();i++) {
        QGraphicsItem *item = collidingItems[i];
            if(typeid(*item) == typeid(mario)) {
                QPointF itemPos = item->pos();
                QRectF boundingRect = item->boundingRect();
                qreal itemw = boundingRect.width();
                qreal itemx = itemPos.x();
                qreal itemy = itemPos.y();
                if(itemx+itemw>=x and itemx<=x+50 and itemy <=y+50 and itemy >= y+47 and hit==0){
                    emit touched();
                    hit=1;
                    setPixmap(QPixmap(":/new/prefix1/image/brick/stone brick.png"));
                }
            }
        }
}

void boxbricks::obj(){
    //coin
    if(item==1){
        Coin::score++;
        if(Coin::scorelabel)
        Coin::scorelabel->setText("Score: " + QString::number(Coin::score));
        //coin
        QGraphicsPixmapItem *coin= new QGraphicsPixmapItem;
        coin->setPixmap(QPixmap(":/new/prefix1/image/item/coin.png"));
        coin->setPos(x,y-60);
        scene()->addItem(coin);
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout,this, [=]()mutable {
            scene()->removeItem(coin);
            delete coin;
            timer->stop();
        });
        timer->start(300);
    }
    //supermushroom
    else if(item==2){
        supermushroom *mushroom = new supermushroom(x,y-50);
        scene()->addItem(mushroom);
    }
    //fireflower
    else if(item==3){
        fireflower *flower = new fireflower(x,y-50);
        scene()->addItem(flower);
    }
}
