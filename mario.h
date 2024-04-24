#ifndef MARIO_H
#define MARIO_H

#include <QGraphicsPixmapItem>
#include<QObject>
#include<QGraphicsView>
#include<QLabel>
class mario :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *reEvent);
    mario(QGraphicsPixmapItem *parent=0);
    void readview(QGraphicsView *view);
    static int hp ;
    static QLabel *hplabel;
    int score = 0, fireBall = 0, faliure = 0;
    bool marioIsDead = false;
public slots:
    void checkKeyState();
    void gravity();
    void animation();
    void countY();
    void lockview();
    void colliedWithFloorBrick();
    //void colliedWithOtherBrick();
    void colliedWithToxicmushroom();
    void HP();
    void InvincibleForm();
    void marioDead();
private:
    bool rightKey = false, leftKey = false,
         upKey = false, faceRight = true, reachTop = false;
    bool collidedTop = false, collidedBottom = true ,collidedLeft = false, collidedRight = false;
    int Rtimer = 0, Ltimer = 0, UPtimer = 0;
    double velocity = 0, Vc = 0, Vg = 0;
    bool increasedHP = false, decreasedHP = false, small = false;
    bool invincible = false;
    int invincibleTimer = 0;
    //for test
    double TopY = 600, BottomY = 0;
    QGraphicsView *view;
};

#endif // MARIO_H
