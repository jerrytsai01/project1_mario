#ifndef MARIO_H
#define MARIO_H

#include <QGraphicsPixmapItem>
#include<QObject>
class mario :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *reEvent);
    mario(QGraphicsPixmapItem *parent=0);
public slots:
    void checkKeyState();
    void gravity();
private:
    bool landed, rightKey = false, leftKey = false, upKey = false;
    int Rtimer = 0, Ltimer = 0;
};

#endif // MARIO_H
