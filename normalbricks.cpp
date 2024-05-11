#include "normalbricks.h"
#include "mario.h"
#include "coin.h"
#include<QTimer>
#include <QList>
#include <QtDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QThread>

normalbricks::normalbricks(int x,int y,int coinsum,QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent),x(x),y(y),coinsum(coinsum)
{
    setPixmap(QPixmap(":/new/prefix1/image/brick/normal brick.png"));
    setPos(x,y);

    QTimer *timer =new QTimer(this);
    connect(timer,&QTimer::timeout,this,&normalbricks::touch);
    timer->start(5);
    connect(this, SIGNAL(jump()), this, SLOT(bounce()));
    connect(this, SIGNAL(jump()), this, SLOT(getcoin()));
}

void normalbricks::touch(){
    if(mario::colliedTopOBJ == this->pos()){
        // touch
        emit jump();
    }
}/*
QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
for (int i =0;i<collidingItems.size();i++) {
    QGraphicsItem *item = collidingItems[i];
        if(typeid(*item) == typeid(mario)) {
            QPointF itemPos = item->pos();
            QRectF boundingRect = item->boundingRect();
            qreal itemw = boundingRect.width();
            qreal itemx = itemPos.x();
            qreal itemy = itemPos.y();
            qDebug()<<itemy;
            if(itemx+itemw>=x and itemx<=x+50 and itemy <=y+50 and itemy >= y+47){
                // touch
                emit jump();
            }
        }
    }*/

void normalbricks::bounce(){
    //setPos(x,y-10);
        qDebug()<<"bounce";
        QTimer *timer = new QTimer(this);
        int count =0;
        connect(timer,&QTimer::timeout,this,[=]()mutable{
            count++;
            if(count ==1){
                setPos(x,y-5);
                y=y-5;
                timer->start(50);
            }
            else if(count ==2){
                setPos(x,y-3);
                y=y-3;
                timer->start(50);
            }
            else if(count ==3){
                setPos(x,y-1);
                y=y-1;
                timer->start(50);
            }
            else if(count ==4){
                setPos(x,y+1);
                y=y+1;
                timer->start(50);
            }
            else if(count ==5){
                setPos(x,y+3);
                y=y+3;
                timer->start(50);
            }
            else if(count ==6){
                setPos(x,y+5);
                y=y+5;
                timer->start(50);
            }
            else {
                timer->stop();
                count =0;
            }
        });
        timer->start(10);
}

void normalbricks::getcoin(){
    if(coinsum>0){
        Coin::score++;
        if(Coin::scorelabel)
        Coin::scorelabel->setText("Score: " + QString::number(Coin::score));
        coinsum--;
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
}


