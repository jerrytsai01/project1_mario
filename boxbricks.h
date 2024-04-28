#ifndef BOXBRICKS_H
#define BOXBRICKS_H
#include <QGraphicsPixmapItem>

class boxbricks: public QObject, public QGraphicsPixmapItem
{
public:
    boxbricks(int x,int y,QGraphicsPixmapItem *parent=0);
};

#endif // BOXBRICKS_H
