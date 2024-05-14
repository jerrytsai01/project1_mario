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


private slots:
    void touch();
    void bounce();
    void getcoin();
    void coinjump();

private :
     int x;
     int y;
     int coinsum;
     int havecoin;

};

#endif // NORMALBRICKS_H
