#ifndef NORMALBRICKS_H
#define NORMALBRICKS_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include "coin.h"

class normalbricks: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    normalbricks(int x,int y,int coinsum,QGraphicsPixmapItem *parent=0);


signals:
    void jump();
    void cjump();


public slots:
    void touch();
    void bounce();
    void getcoin();
    void coinjump();
    void reset();

private :
     int x;
     int y;
     int coinsum;
     int icoinsum;
     int havecoin;

};

#endif // NORMALBRICKS_H
