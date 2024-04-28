#ifndef NORMALBRICKS_H
#define NORMALBRICKS_H
#include <QGraphicsPixmapItem>

class normalbricks: public QObject, public QGraphicsPixmapItem
{
public:
    normalbricks(int x,int y,QGraphicsPixmapItem *parent=0);
};

#endif // NORMALBRICKS_H
