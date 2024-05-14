#include "brokenbricks.h"
#include "mario.h"
#include <QTimer>
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
    timer->start(5);
}

void brokenbricks::bounce(){
    if(mario::colliedTopOBJ == this->pos()){
        scene()->removeItem(this);
        delete this;
        return;
    }
}

