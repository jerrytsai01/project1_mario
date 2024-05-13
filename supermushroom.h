#ifndef SUPERMUSHROOM_H
#define SUPERMUSHROOM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsView>
class supermushroom: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    supermushroom(int X,int Y,QGraphicsPixmapItem *parent = 0);
    void readview(QGraphicsView *view);
public slots:
    void eaten_by_mario();
    void supermushroom_move();
    void gravity();
    void countY();
    void collidedWithBrick();
private:
    bool collidedBottom = false, collidedLeft = false, collidedRight = false, collidedTop = false;
    bool faceRight = true;
    double Vg = 0, acceleration;
    int Deathtime = 0;
};

#endif // SUPERMUSHROOM_H
