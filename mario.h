#ifndef MARIO_H
#define MARIO_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsView>
#include <QLabel>
#include <QMouseEvent>
#include "flag.h"
class mario :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *reEvent);
    using QGraphicsPixmapItem::mousePressEvent;
    void fireEvent(QPoint aimPos);
    mario(QGraphicsPixmapItem *parent=0);
    void readview(QGraphicsView *view);
    static int hp ;
    static QLabel *hplabel;
    int score = 0, fireBall = 100, faliure = 0;
    bool marioIsDead = false, win = false;
    bool collidedTop;
    bool fire = false, small = false;
    flag *Flag;
    static QPointF colliedTopOBJ;
public slots:
    void checkKeyState();
    void gravity();
    void animation();
    void countY();
    void lockview();
    void colliedWithFloorBrick();
    //void colliedWithOtherBrick();
    void colliedWithMushroom();
    void eatFireflower();
    void HP();
    void InvincibleForm();
    void marioDead();
    void winEvent();
private:
    bool rightKey = false, leftKey = false,
         upKey = false, faceRight = true, reachTop = false;
    bool collidedBottom = true ,collidedLeft = false, collidedRight = false;
    int Rtimer = 0, Ltimer = 0, UPtimer = 0, cTopTimer = 0;
    double velocity = 0, Vc = 0, Vg = 0;
    bool increasedHP = false, decreasedHP = false;
    bool invincible = false;
    int invincibleTimer = 0;
    //for test
    double TopY = 600, BottomY = 0;
    int numberofBullet = 100;
    bool shooterform = true, canshoot = false, flagExist = false;
    QGraphicsView *view;
    ~mario();
};

#endif // MARIO_H
