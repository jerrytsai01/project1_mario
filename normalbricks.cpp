#include "normalbricks.h"

normalbricks::normalbricks(int x,int y,QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{
    setPixmap(QPixmap(":/new/prefix1/image/brick/normal brick.png"));
    setPos(x,y);
}
