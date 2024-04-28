#include "boxbricks.h"
#include<QTimer>

boxbricks::boxbricks(int x,int y,QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{
    setPixmap(QPixmap(":/new/prefix1/image/brick/box brick.png"));
    setPos(x,y);
}
