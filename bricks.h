#ifndef BRICKS_H
#define BRICKS_H

#include <QGraphicsPixmapItem>

class bricks : public QGraphicsPixmapItem
{
public:
    bricks(const QPixmap &pixmap, int x, int y, QGraphicsItem *parent = nullptr);
};
#endif // BRICKS_H
