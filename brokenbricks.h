#ifndef BROKENBRICKS_H
#define BROKENBRICKS_H
#include <QGraphicsPixmapItem>

class brokenbricks: public QObject, public QGraphicsPixmapItem
{
public:
    brokenbricks(int x,int y,QGraphicsPixmapItem *parent=0);

private slots:
    void bounce();

private :
    int x;
    int y;
};

#endif // BROKENBRICKS_H
