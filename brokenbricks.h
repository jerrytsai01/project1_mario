#ifndef BROKENBRICKS_H
#define BROKENBRICKS_H
#include <QGraphicsPixmapItem>

class brokenbricks: public QObject, public QGraphicsPixmapItem
{
public:
    brokenbricks(int x,int y,QGraphicsPixmapItem *parent=0);

public slots:
    void bounce();

private :
    int x;
    int y;
    int DeathTime = 0;
};

#endif // BROKENBRICKS_H
