#ifndef MARIO_H
#define MARIO_H

#include <QGraphicsPixmapItem>
#include<QObject>
#include<QGraphicsView>
class mario :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *reEvent);
    mario(QGraphicsPixmapItem *parent=0);
    void readview(QGraphicsView *view);
public slots:
    void checkKeyState();
    void gravity();
    void animation();
    void countY();
    void lockview();
    void colliedWithBrick();
private:
    bool rightKey = false, leftKey = false,
         upKey = false, faceRight = true, reachTop = false;
    bool collidedTop = false, collidedBottom = true ,collidedLeft = false, collidedRight = false;
    int Rtimer = 0, Ltimer = 0, UPtimer = 0;
    double velocity = 0, Vc = 0, Vg = 0;
    QGraphicsView *view;
};

#endif // MARIO_H
