#include "mario.h"
#include<QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>

mario::mario(QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{
    landed = false;

    //初始位置跟圖片
    setPos(3300,450);
    setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_R.png"));

    //持續偵測的計時
    QTimer*timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkKeyState()));
    connect(timer, SIGNAL(timeout()), this, SLOT(animation()));
    connect(timer, SIGNAL(timeout()), this, SLOT(countY()));
    connect(timer, SIGNAL(timeout()),this,SLOT(gravity()));
    timer->start(10);

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
    if((event->key() == Qt::Key_Up)&&((landed == true)||y() == 450)){
        qDebug() << "jump";
        upKey = true;
        //setPos(x(),y()-150);
    }
}

//按鍵放開事件
void mario::keyReleaseEvent(QKeyEvent *reEvent)
{
    if (reEvent->isAutoRepeat()) {
            // 如果是自动重复触发的事件，直接忽略
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
        velocity = 0;
        setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_L.png"));
    }
}

//因應按鍵按下改變位置
void mario::checkKeyState()
{
    if(rightKey == true){
        setPos(x()+2,y());
    }
    if((leftKey == true)&&(x()>0)){
        setPos(x()-2,y());
    }
    if(upKey){
        UPtimer++;
        if(UPtimer <= 20){
            velocity = -53;
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
    if(!landed){
        double acceleration = 0.08; // 加速度
        Vg += acceleration;
    }
}

void mario::countY(){
    Vc = Vg + velocity;
    qDebug() <<"Vc:" << Vc << "; Vg" << Vg << "; velocity:" << velocity;

    if(y()>=450&&Vc>=0){   //如果y==450且VC>=0則將速度和位置歸零
        landed = true;
        Vg = 0;
        Vc = 0;
        setPos(x(), 450);
        qDebug() << "s";
    }
    if(upKey||!landed){ //按下上鍵
        landed = false;
        setPos(x(), y()+Vc);
        qDebug() << "up";
    }
}


void mario::animation()
{
    if(rightKey) {
        Rtimer++; // 增加計數器
        if(Rtimer % 100 < 50) { // 控制切換速度
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run2_R.png"));
        } else {
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run1_R.png"));
        }
    }
    if(leftKey){
        Ltimer++;
        if(Ltimer%100 < 50)
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run2_L.png"));
        if(Ltimer%100 >= 50)
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run1_L.png"));
    }
}


