#include "coin.h"
#include <QTimer>
#include <QList>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <typeinfo>
#include "mario.h"
#include <QLabel>
int Coin::score = 0;
QLabel *Coin::scorelabel = nullptr;
Coin::Coin(int x,int y,QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{
    setPos(x,y);

    setPixmap(QPixmap(":/new/prefix1/image/item/coin.png"));
    QTimer *timer =new QTimer(this);
    connect(timer,&QTimer::timeout,this,&Coin::touch);
    timer->start(10);
    connect(this, SIGNAL(collected()), this, SLOT(getcoin()));
}


void Coin::touch(){
    QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
    for (int i =0;i<collidingItems.size();i++) {
        QGraphicsItem *item = collidingItems[i];
            if(typeid(*item) == typeid(mario)) {
                // 角色与硬币相交，发射信号
                emit collected();
                //score++;
                //scorelabel->setText("Score: " + QString::number(score));

                // 删除硬币
                scene()->removeItem(this);
                delete this;
                return;
            }
        }
}



void Coin::getcoin(){
    score++;
    if(scorelabel)
        scorelabel->setText("Score: " + QString::number(score));
}

