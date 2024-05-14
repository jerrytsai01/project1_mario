#ifndef TOXICMUSHROOM_H
#define TOXICMUSHROOM_H


#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsView>
class toxicmushroom: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public :
    toxicmushroom(int X,int Y,QGraphicsPixmapItem *parent=0);
    void readview(QGraphicsView *view);
public slots:
    void livecheck();
    void toxicmushroom_move();
    void gravity();
    void animation();
    void countY();
    void colliedWithBrick();
    void colliedWithMario();
    void hitByBullet();

private :
    bool collidedTop = false, collidedBottom = true ,collidedLeft = false, collidedRight = false;
    bool faceLeft = true;
    double velocity = 0;
    int timer = 0, deathTimer = 0;
    bool live = true;
    QGraphicsView *view;
    int x;
    int y;
    int ix;
    int iy;
};


#endif // TOXICMUSHROOM_H
