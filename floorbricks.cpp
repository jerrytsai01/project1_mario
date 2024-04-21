#include "floorbricks.h"
#include "QGraphicsPixmapItem"

floorBricks::floorBricks(const QPixmap &pixmap, int x, int y, QGraphicsItem *parent): QGraphicsPixmapItem(pixmap, parent)
{
    setPos(x, y);
}
