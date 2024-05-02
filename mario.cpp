#include "mario.h"
#include "mainwindow.h"
#include "floorbricks.h"
#include "stonebricks.h"
#include "brokenbricks.h"
#include "normalbricks.h"
#include "boxbricks.h"
#include "toxicmushroom.h"
#include "supermushroom.h"
#include "fireflower.h"
#include "waterpipe.h"
#include "flag_pole.h"
#include "bullet.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QtWidgets>
#include <QList>
#include <typeinfo>

int mario::hp = 3;
QLabel *mario::hplabel=nullptr;
mario::mario(QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
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
    connect(timer, SIGNAL(timeout()), this, SLOT(colliedWithMushroom()));
    connect(timer, SIGNAL(timeout()), this, SLOT(eatFireflower()));
    connect(timer, SIGNAL(timeout()), this, SLOT(shooting()));
    connect(timer, SIGNAL(timeout()), this, SLOT(Shooterform()));
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

    if(event->key() == Qt::Key_Left or event->key() == Qt::Key_A){
        leftKey = true;
    }
    if(event->key() == Qt::Key_Right or event->key() == Qt::Key_D){
        rightKey = true;
    }
    if((event->key() == Qt::Key_Up or event->key() == Qt::Key_W)&&collidedBottom){
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
    if (reEvent->key() == Qt::Key_Right or reEvent->key() == Qt::Key_D) {
        rightKey = false;
        faceRight = true;
        if(small)
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_R.png"));
        else
            setPixmap(QPixmap(":/new/prefix1/image/Mario_big/mario_R_stand.png"));
    }
    if (reEvent->key() == Qt::Key_Left or reEvent->key() == Qt::Key_A) {
        leftKey = false;
        faceRight = false;
        Ltimer = 0;
        if(small)
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_L.png"));
        else
            setPixmap(QPixmap(":/new/prefix1/image/Mario_big/mario_L_stand.png"));
    }
    if (reEvent->key() == Qt::Key_Up or reEvent->key() == Qt::Key_W) {
        upKey = false;
        UPtimer = 0;
        //velocity = 0;
        if(small)
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_L.png"));
        else
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
        }//else;
        //qDebug()<<"stopped Right";
    }
    if((leftKey == true)&&(x()>0)){
        if(!collidedLeft){
            faceRight = false;
            setPos(x()-2,y());}
        //else;
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
        double acceleration;
        if(small)
            acceleration = 0.15; // 加速度
        else
            acceleration = 0.09;
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
        //qDebug() << "from " << BottomY << " to " << TopY << " high " << BottomY - TopY;
        //qDebug() <<"Vc:" << Vc << "; Vg" << Vg << "; velocity:" << velocity;
        //qDebug() << "countY:collideBottom:" << collidedBottom <<"; collideTop:" <<collidedTop;
    }
    setPos(x(), y()+Vc);
    if(y() < TopY)
        TopY = y();
    //qDebug() << "Y = " << y()-Vc << "+" << Vc;
}
//change the skin of mario
void mario::animation()
{
    qDebug() << pos();
    if(rightKey&&collidedBottom) {
        Rtimer++; // 增加計數器
        if(small){
            if(Rtimer % 50 < 25) { // 控制切換速度
                setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run2_R.png"));
            } else {
                setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run1_R.png"));
            }
        }
        else{
            if(Rtimer % 50 < 25) { // 控制切換速度
                setPixmap(QPixmap(":/new/prefix1/image/Mario_big/mario_R_run2.png"));
            } else {
                setPixmap(QPixmap(":/new/prefix1/image/Mario_big/mario_R_run1.png"));
            }
        }
    }
    else if(leftKey&&collidedBottom){
        Ltimer++;
        if(small){
            if(Ltimer % 50 < 25)
                setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run2_L.png"));
            else
                setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run1_L.png"));
        }
        else{
            if(Ltimer % 50 < 25)
                setPixmap(QPixmap(":/new/prefix1/image/Mario_big/mario_L_run2.png"));
            else
                setPixmap(QPixmap(":/new/prefix1/image/Mario_big/mario_L_run1.png"));
        }
    }
    else if(!collidedBottom){
        UPtimer++;
        if(small){//small mario up
            if(faceRight)
                setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_jump1_R.png"));
            else
                setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_jump1_L.png"));
        }
        else{//big mario up
            if(faceRight){
                setPixmap(QPixmap(":/new/prefix1/image/Mario_big/mario_R_jump1.png"));
            }
            else{
                setPixmap(QPixmap(":/new/prefix1/image/Mario_big/mario_L_jump1.png"));
            }
        }
    }
    else{
        if(small){
            if(faceRight)
                setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_R.png"));
            else
                setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_L.png"));
        }
        else{
            if(faceRight)
                setPixmap(QPixmap(":/new/prefix1/image/Mario_big/mario_R_stand.png"));
            else
                setPixmap(QPixmap(":/new/prefix1/image/Mario_big/mario_L_stand.png"));
        }
    }
}

void mario::fireEvent(QPoint aimPos){
    qDebug() << "shoot";
    if(numberofBullet>0){
        bullet * BULLET = new bullet();
        scene()->addItem(BULLET);
        BULLET-> setTargetPosition(aimPos, pos());
        numberofBullet--;
        qDebug() << "shoot a bullet";
        qDebug() << "mario now has " << numberofBullet << " bullets";
        //if (event->isAutoRepeat())
            //return;
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
            //qDebug() << "collided floor brick";
            //qDebug() << "size: x from" << item->x()-25 << " to " << item->x()+25 << ";y from" << item->y()-50 << " to " << item->y()+50;
            //qDebug() <<"mario x" <<x()<<" y "<<y();
            if(small){
                if((item->y() > y()) && (x() < item->x()+26) && (x() > item->x()-26)){
                    if(!upKey&&velocity!=0){
                        velocity = 0;
                        Vg = 0;
                        Vc = 0;
                    }
                    BottomY = y();
                    collidedBottom = true;
                }
                else if((item->x() >= x()) && (y() > item->y()-48) && (y() < item->y()+50)){
                    setPos(x(),y()-0.1);
                    //qDebug() << "111111111111111";
                    collidedRight = true;
                }
                else if((item->x() <= x()) && (y() > item->y()-48) && (y() < item->y()+50)){
                    setPos(x(),y()-0.1);
                    collidedLeft = true;
                }
            }
            //big mario collide
            else{
                if((item->y() > y()) && (x() < item->x()+28) && (x() > item->x()-28)){
                    if(!upKey&&velocity!=0){
                        velocity = 0;
                        Vg = 0;
                        Vc = 0;
                    }
                    BottomY = y();
                    collidedBottom = true;
                }
                else if((item->x() >= x()) && (y() > item->y()-60) && (y() < item->y()+60)){
                    setPos(x(),y()-0.1);
                    //qDebug() << "111111111111111";
                    collidedRight = true;
                }
                else if((item->x() <= x()) && (y() > item->y()-68) && (y() < item->y()+68)){
                    setPos(x(),y()-0.1);
                    collidedLeft = true;
                }
            }
        }
        if(typeid(*item) == typeid(stonebricks) or typeid(*item) == typeid(brokenbricks)){
            //qDebug() << "collided stone brick";
            //qDebug() << "size: x from" << item->x()-25 << " to " << item->x()+25 << ";y from" << item->y()-25 << " to " << item->y()+25;
            //qDebug() <<"mario x" <<x()<<" y "<<y();
            if(small){
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
                    upKey = false;
                }
                if((item->x() > x()) && (y() > item->y()-25) && (y() < item->y()+25))
                    collidedRight = true;
                if((item->x() < x()) && (y() > item->y()-25) && (y() < item->y()+25))
                    collidedLeft = true;
            }
            else{
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
                    upKey = false;
                }
                if((item->x() > x()) && (y() > item->y()-68) && (y() < item->y()+68))
                    collidedRight = true;
                if((item->x() < x()) && (y() > item->y()-68) && (y() < item->y()+68))
                    collidedLeft = true;
            }
        }
        if(typeid(*item) == typeid(waterpipe)){
            if(small){
                if((item->y() > y()) && (x() < item->x()+48) && (x() > item->x()-90)){
                    if(!upKey&&velocity!=0){
                        velocity = 0;
                        Vg = 0;
                        Vc = 0;
                    }
                    BottomY = y();
                    collidedBottom = true;
                }
                if((item->x() >= x()) && (y()+50 > item->y()) && (y() < item->y()+100)){
                    setPos(x(),y()-0.2);
                    collidedRight = true;
                }
                if((item->x() <= x()) && (y()+50 > item->y()) && (y() < item->y()+100)){
                    setPos(x(),y()-0.2);
                    collidedLeft = true;
                }
            }
            //big mario collide
            else{
                if((item->y() > y()) && (x() < item->x()+56) && (x() > item->x()-100)){
                    if(!upKey&&velocity!=0){
                        velocity = 0;
                        Vg = 0;
                        Vc = 0;
                    }
                    BottomY = y();
                    collidedBottom = true;
                }
                else if((item->x() >= x()) && (y() > item->y()) && (y() < item->y()+100)){
                    collidedRight = true;
                }
                else if((item->x() <= x()) && (y() > item->y()) && (y() < item->y()+100)){
                    collidedLeft = true;
                }
            }
        }
        if(typeid(*item) == typeid(flag_pole)){

        }
        //qDebug() << "collideBottom:" <<collidedBottom << "; collideR:" << collidedRight << "; collideL:" << collidedLeft <<"; CollideTop:" <<collidedTop;
    }
}

void mario::colliedWithMushroom(){
    decreasedHP = false;
    QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
    for(int i =0;i<collidingItems.size();i++){
        QGraphicsItem *item = collidingItems[i];
        if((typeid(*item) == typeid(toxicmushroom)) && !invincible){
            //qDebug() << "collided toxicmushroom";
            //qDebug() << "size: x from" << item->x()-25 << " to " << item->x()+25 << ";y from" << item->y()-50 << " to " << item->y()+50;
            //qDebug() <<"mario x" <<x()<<" y "<<y();
            if((item->y() > y()) && (x() < item->x()+25) && (x() > item->x()-25))
                decreasedHP = true;
            else if((item->x() < x()) && (y() > item->y()-48) && (y() < item->y()+48))
                decreasedHP = true;
            else if((item->x() > x()) && (y() > item->y()-48) && (y() < item->y()+48))
                decreasedHP = true;
            if(decreasedHP)
                invincible = true;
        }
        if(typeid(*item) == typeid (supermushroom)){
            setPos(x(), y()-10);
            small = false;
            qDebug() << "small : " << small;
        }
    }
    //qDebug() << "decreasedHP = " << decreasedHP ;
}
//吃火焰花
void mario::eatFireflower(){
    QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
    for(int i =0;i<collidingItems.size();i++){
        QGraphicsItem *item = collidingItems[i];
        if((typeid(*item) == typeid(fireflower))){
            numberofBullet += 3;
        }
    }
}
//if blood == 0, respawn to begin
void mario::marioDead()
{
    if((hp <= 0)||(y() >= 650)){
        //qDebug() << "FAILURE!!!";
        small = true;
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
    //qDebug() << "HP = " << hp;
    hplabel->setText("HP: " + QString::number(hp));
}

void mario::InvincibleForm(){
    if(invincible) {
        invincibleTimer++;
        //qDebug() << "Mario is in the invincible form.";
    }
    if(invincibleTimer >= 400){
        invincible = false;
        invincibleTimer = 0;
        //qDebug() << "Mario return the normal form.";
    }
}

