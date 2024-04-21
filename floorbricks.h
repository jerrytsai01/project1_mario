#ifndef FLOORBRICKS_H
#define FLOORBRICKS_H

#include <QGraphicsPixmapItem>
class floorBricks: public QGraphicsPixmapItem
{
public:
    floorBricks(const QPixmap &pixmap, int x, int y, QGraphicsItem *parent = nullptr);
};

#endif // FLOORBRICKS_H
