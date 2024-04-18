#include "mario.h"
#include<QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>

mario::mario(QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{
    landed = false;

    //初始位置跟圖片
    setPos(0,450);
    setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_R.png"));

    //持續偵測的計時
    QTimer*timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(gravity()));
    connect(timer, SIGNAL(timeout()), this, SLOT(checkKeyState()));
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
        setPos(x(),y()-200);
    }
}

//按鍵放開事件
void mario::keyReleaseEvent(QKeyEvent *reEvent)
{
    if (reEvent->key() == Qt::Key_Right) {
        rightKey = false;
        Rtimer = 0;
        setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_R.png"));
    }
    if (reEvent->key() == Qt::Key_Left) {
        leftKey = false;
        Ltimer = 0;
        setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_L.png"));
    }
}

//因應按鍵按下改變位置
void mario::checkKeyState()
{
    if(rightKey == true){
        setPos(x()+10,y());
        Rtimer++;
        if(Rtimer%10 < 5)
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run2_R.png"));
        else
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run1_R.png"));
    }
    if((leftKey == true)&&(x()>0)){
        setPos(x()-10,y());
        Ltimer++;
        if(Ltimer%10 < 5)
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run2_L.png"));
        else
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run1_L.png"));
    }

}

//給持續向下速度
void mario::gravity(){
    if(!landed&&y() < 450){
        qDebug() << "1" <<endl;
        setPos(x(),y()+5);
    }
}


