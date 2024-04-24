#include "mario.h"
#include "mainwindow.h"
#include "floorbricks.h"
#include "stonebricks.h"
#include "toxicmushroom.h"
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QList>
#include <typeinfo>

mario::mario(QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    //初始位置跟圖片
    setPos(0,400);
    setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_R.png"));

    //持續偵測的計時
    QTimer*timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkKeyState()));
    connect(timer, SIGNAL(timeout()), this, SLOT(animation()));
       connect(timer, SIGNAL(timeout()), this, SLOT(gravity()));
    connect(timer, SIGNAL(timeout()), this, SLOT(lockview()));
    //connect(timer, SIGNAL(timeout()), this, SLOT(colliedWithBrick()));
    connect(timer, SIGNAL(timeout()), this, SLOT(marioDead()));
    connect(timer, SIGNAL(timeout()), this, SLOT(colliedWithToxicmushroom()));
    connect(timer, SIGNAL(timeout()), this, SLOT(HP()));
    timer->start(10);

    QTimer *Timer2 = new QTimer(this);
    connect(Timer2, SIGNAL(timeout()), this, SLOT(colliedWithFloorBrick()));
    connect(Timer2, SIGNAL(timeout()), this, SLOT(countY()));
    connect(Timer2, SIGNAL(timeout()), this, SLOT(InvincibleForm()));
    Timer2->start(5);

}
void mario::readview(QGraphicsView *read){
    view=read;
}
void mario::lockview(){
    if((pos().x()>=700) || (pos().x()<=6300)){
        view->centerOn(pos().x(),300);
    }
}
//按鍵按下事件
void mario::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key_Left){
        leftKey = true;
    }
    if(event->key() == Qt::Key_Right){
       rightKey = true;
    }
    if((event->key() == Qt::Key_Up)&&collidedBottom){
        //qDebug() << "jump";
        upKey = true;
        //setPos(x(),y()-150);
    }
}

//按鍵放開事件
void mario::keyReleaseEvent(QKeyEvent *reEvent)
{
    if (reEvent->isAutoRepeat()) {
            // ignore auto event
            return;
        }
    if (reEvent->key() == Qt::Key_Right) {
        rightKey = false;
        faceRight = true;
        setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_R.png"));
    }
    if (reEvent->key() == Qt::Key_Left) {
        leftKey = false;
        faceRight = false;
        Ltimer = 0;
        setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_L.png"));
    }
    if (reEvent->key() == Qt::Key_Up) {
        upKey = false;
        UPtimer = 0;
        //velocity = 0;
        setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_L.png"));
    }
}

//因應按鍵按下改變位置
void mario::checkKeyState()
{    
    if(rightKey == true&&x()<7000){
        if(!collidedRight){
            faceRight = true;
            setPos(x()+2,y());
        }else;
            //qDebug()<<"stopped Right";
    }
    if((leftKey == true)&&(x()>0)){
        if(!collidedLeft){
        faceRight = false;
        setPos(x()-2,y());}
        else;
            //qDebug()<<"stopped Left";
    }
    if(upKey){
        UPtimer++;
        if(UPtimer <= 50){
            velocity = -4;
        }
        else{
            upKey = false;
            UPtimer = 0;
            //velocity = 0;
        }
    }
}

//給持續向下速度
void mario::gravity(){
        //collidedBottom = false;
    if(!collidedBottom){
        double acceleration = 0.12; // 加速度
        Vg += acceleration;
        //qDebug() << y();
    }
}

//Vc = Vg + V --> Y+=Vc
void mario::countY(){
    Vc = Vg + velocity;
    if(Vc >= 4)
        Vc = 4;
    //

    if(((collidedBottom)&&(Vc>=0))||((collidedTop)&&(Vc<0))){   //如果y==450且VC>=0則將速度和位置歸零
        collidedBottom = true;
        velocity = 0;
        Vg = 0;
        Vc = 0;

        //qDebug() <<"Vc:" << Vc << "; Vg" << Vg << "; velocity:" << velocity;
        //qDebug() << "countY:collideBottom:" << collidedBottom <<"; collideTop:" <<collidedTop;
    }
    setPos(x(), y()+Vc);
    //qDebug() << "Y = " << y()-Vc << "+" << Vc;
}

//change the skin of mario
void mario::animation()
{
    if(rightKey&&collidedBottom) {
        Rtimer++; // 增加計數器
        if(Rtimer % 50 < 25) { // 控制切換速度
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run2_R.png"));
        } else {
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run1_R.png"));
        }
    }
    else if(leftKey&&collidedBottom){
        Ltimer++;
        if(Ltimer % 50 < 25)
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run2_L.png"));
        else
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run1_L.png"));
    }
    else if(!collidedBottom){
        if(upKey){
            if(faceRight)
                setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_jump1_R.png"));
            else
                setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_jump1_L.png"));
        }
        else{
            if(faceRight)
                setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_jump2_R.png"));
            else
                setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_jump2_L.png"));
        }
    }
    else{
        if(faceRight)
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_R.png"));
        else
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_L.png"));
    }
}

//if collied with brick, record the direction of collision
void mario::colliedWithFloorBrick()
{
    collidedBottom = false;
    collidedRight = false;
    collidedLeft = false;
    collidedTop = false;
    QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
    for(int i =0;i<collidingItems.size();i++){
        QGraphicsItem *item = collidingItems[i];
        //if collided with block type
        if(typeid(*item) == typeid(floorBricks)){
            //qDebug() << "Collided with floor brick";
        } else if(typeid(*item) == typeid(stonebricks)){
            //qDebug() << "Collided with stone brick";
        }
        if(typeid(*item) == typeid(floorBricks)){
            //qDebug() << "collided floor brick";
            //qDebug() << "size: x from" << item->x()-25 << " to " << item->x()+25 << ";y from" << item->y()-50 << " to " << item->y()+50;
            //qDebug() <<"mario x" <<x()<<" y "<<y();
            if((item->y() > y()) && (x() < item->x()+26) && (x() > item->x()-26)){
                if(!upKey&&velocity!=0){
                velocity = 0;
                Vg = 0;
                Vc = 0;
                }
                collidedBottom = true;
            }
            else if((item->x()-25 >= x()) && (y() > item->y()-48) && (y() < item->y()+50)){
                setPos(x(),y()-0.1);
                //qDebug() << "111111111111111";
                collidedRight = true;
            }
            else if((item->x()+25 <= x()) && (y() > item->y()-48) && (y() < item->y()+50)){
                setPos(x(),y()-0.1);
                collidedLeft = true;
            }
        }
        if(typeid(*item) == typeid(stonebricks)){
            //qDebug() << "collided stone brick";
            //qDebug() << "size: x from" << item->x()-25 << " to " << item->x()+25 << ";y from" << item->y()-25 << " to " << item->y()+25;
            //qDebug() <<"mario x" <<x()<<" y "<<y();
            if((item->y() > y()) && (x() < item->x()+40) && (x() > item->x()-40)){
                if(!upKey&&velocity!=0){
                    velocity = 0;
                    Vg = 0;
                    Vc = 0;
                }
                collidedBottom = true;
            }
            if((item->y() < y()) && (x() < item->x()+40) && (x() > item->x()-40)){
                collidedTop = true;
            }
            if((item->x() > x()) && (y() > item->y()-25) && (y() < item->y()+25))
                collidedRight = true;
            if((item->x() < x()) && (y() > item->y()-25) && (y() < item->y()+25))
                collidedLeft = true;
            }
    }
    //qDebug() << "collideBottom:" <<collidedBottom << "; collideR:" << collidedRight << "; collideL:" << collidedLeft <<"; CollideTop:" <<collidedTop;
}

void mario::colliedWithToxicmushroom(){
    decreasedHP = false;
    QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
    for(int i =0;i<collidingItems.size();i++){
        QGraphicsItem *item = collidingItems[i];
        if((typeid(*item) == typeid(toxicmushroom)) && !invincible){
            qDebug() << "collided toxicmushroom";
            qDebug() << "size: x from" << item->x()-25 << " to " << item->x()+25 << ";y from" << item->y()-50 << " to " << item->y()+50;
            qDebug() <<"mario x" <<x()<<" y "<<y();
            if((item->y() > y()) && (x() < item->x()+25) && (x() > item->x()-25))
                decreasedHP = true;
            else if((item->x() < x()) && (y() > item->y()-48) && (y() < item->y()+48))
                decreasedHP = true;
            else if((item->x() > x()) && (y() > item->y()-48) && (y() < item->y()+48))
                decreasedHP = true;
            if(decreasedHP)
                invincible = true;
        }
    }
    qDebug() << "decreasedHP = " << decreasedHP ;
}

//if blood == 0, respawn to begin
void mario::marioDead()
{
    if((hp <= 0)||(y() >= 650)){
        //qDebug() << "FAILURE!!!";

        setPos(0, 400);
        hp = 3;
        faliure++;
    }
}

void mario::HP(){
    if(increasedHP){
        hp++;
        increasedHP = false;
    }
    if (decreasedHP)
        hp--;
    qDebug() << "HP = " << hp;
}

void mario::InvincibleForm(){
    if(invincible) {
        invincibleTimer++;
        qDebug() << "Mario is in the invincible form.";
    }
    if(invincibleTimer >= 400){
        invincible = false;
        invincibleTimer = 0;
        qDebug() << "Mario return the normal form.";
    }
}

