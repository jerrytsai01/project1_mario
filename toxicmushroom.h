#ifndef TOXICMUSHROOM_H
#define TOXICMUSHROOM_H


#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsView>
class toxicmushroom: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public :
    toxicmushroom(QGraphicsPixmapItem *parent=0);
    void readview(QGraphicsView *view);
public slots:
    void toxicmushroom_move();
    void gravity();
    void countY();
    void colliedWithBrick();
private :
    bool collidedTop = false, collidedBottom = true ,collidedLeft = false, collidedRight = false;
    bool faceLeft = true;
    double velocity = 0;
    QGraphicsView *view;
};


#endif // TOXICMUSHROOM_H
