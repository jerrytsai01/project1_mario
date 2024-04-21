#include "bricks.h"
#include "QPixmap"
#include "QGraphicsPixmapItem"

bricks::bricks(const QPixmap &pixmap, int x, int y, QGraphicsItem *parent)
    : QGraphicsPixmapItem(pixmap, parent)
{
    setPos(x, y); // 设置砖块位置
}
