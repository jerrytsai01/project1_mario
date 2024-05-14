#include "flag.h"
#include "QGraphicsPixmapItem"
flag::flag(QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{
    setPixmap(QPixmap(":/new/prefix1/image/item/flag.png"));
    setPos(6610,50);
}
