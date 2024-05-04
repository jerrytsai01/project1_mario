#include "brokenbricks.h"
#include "mario.h"
#include<QTimer>
#include <QList>
#include <QtDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

brokenbricks::brokenbricks(int x,int y,QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent),x(x),y(y)
{
    setPixmap(QPixmap(":/new/prefix1/image/brick/broken brick.png"));
    setPos(x,y);

    QTimer *timer =new QTimer(this);
    connect(timer,&QTimer::timeout,this,&brokenbricks::bounce);
    timer->start(7);
}

void brokenbricks::bounce(){
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
                    //DeathTime++;
                    //if(DeathTime > 3){
                    // delete
                    // mario::collidedTop=true;
                    scene()->removeItem(this);
                    delete this;
                    return;
                    //}
                }
            }
        }
}
