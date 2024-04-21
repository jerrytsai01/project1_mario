#include "mario.h"
#include "mainwindow.h"
#include "floorbricks.h"
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QList>
#include <typeinfo>

mario::mario(QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{

    //初始位置跟圖片
    setPos(0,400);
    setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_stand_R.png"));

    //持續偵測的計時
    QTimer*timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkKeyState()));
    connect(timer, SIGNAL(timeout()), this, SLOT(animation()));
    connect(timer, SIGNAL(timeout()), this, SLOT(countY()));
    connect(timer, SIGNAL(timeout()), this, SLOT(gravity()));
    connect(timer, SIGNAL(timeout()), this, SLOT(lockview()));
    connect(timer, SIGNAL(timeout()), this, SLOT(colliedWithBrick()));
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
    if((event->key() == Qt::Key_Up)&&collidedBottom){
        qDebug() << "jump";
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
        }else
            qDebug()<<"stopped Right";
    }
    if((leftKey == true)&&(x()>0)){
        if(!collidedLeft){
        faceRight = false;
        setPos(x()-2,y());}
        else
            qDebug()<<"stopped Left";
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
        double acceleration = 0.08; // 加速度
        Vg += acceleration;
        //qDebug() << y();
    }
}

//Vc = Vg + V --> Y+=Vc
void mario::countY(){
    Vc = Vg + velocity;
    //
    if(((collidedBottom)&&(Vc>=0))||(collidedTop)){   //如果y==450且VC>=0則將速度和位置歸零
        collidedBottom = true;
        velocity = 0;
        Vg = 0;
        Vc = 0;
        qDebug() <<"Vc:" << Vc << "; Vg" << Vg << "; velocity:" << velocity;
        qDebug() << "countY:collideBottom:" << collidedBottom <<"; collideTop:" <<collidedTop;
    }
    setPos(x(), y()+Vc);
    qDebug() << "Y = " << y()-Vc << "+" << Vc;
}

//change the skin of mario
void mario::animation()
{
    if(rightKey&&collidedBottom) {
        Rtimer++; // 增加計數器
        if(Rtimer % 100 < 50) { // 控制切換速度
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run2_R.png"));
        } else {
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run1_R.png"));
        }
    }
    else if(leftKey&&collidedBottom){
        Ltimer++;
        if(Ltimer%100 < 50)
            setPixmap(QPixmap(":/new/prefix1/image/Mario_small/s_mario_run2_L.png"));
        if(Ltimer%100 >= 50)
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

void mario::readview(QGraphicsView *read){
    view=read;
}
void mario::lockview(){
    if((pos().x()>=700) || (pos().x()<=6300)){
        view->centerOn(pos().x(),300);
    }
}

//if collied with brick, record the direction of collision
void mario::colliedWithBrick()
{
    collidedBottom = false;
    collidedLeft = false;
    collidedLeft = false;
    collidedTop = false;
    QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
    for(int i =0;i<collidingItems.size();i++){
        QGraphicsItem *item = collidingItems[i];
        if(typeid(*item) == typeid(floorBricks)){
            qDebug() << "collided floor brick";
            qDebug() << "size: x from" << item->x()-25 << " to " << item->x()+25 << ";y from" << item->y()-50 << " to " << item->y()+50;
            qDebug() <<"mario x" <<x()<<" y "<<y();
            if((item->y()-75 <= y()) && (x() < item->x()+25) && (x() > item->x()-25))
                collidedBottom = true;
            if((item->x()-25 >= x()) && (y() > item->y()-49.5) && (y() < item->y()+49.5))
                collidedRight = true;
            if((item->x()+25 <= x()) && (y() > item->y()-49.5) && (y() < item->y()+49.5))
                collidedLeft = true;

            /*
            collidedBottom = true;
            collidedLeft = true;
            collidedLeft = true;
            collidedTop = true;

            //gain the rect of objectrect
            QRectF itemRect = item->boundingRect();
            QPointF itemTopLeft = item->mapToScene(itemRect.topLeft());
            QPointF itemBottomRight = item->mapToScene(itemRect.bottomRight());

            //gain the rect of mario
            QRectF marioRect = this->boundingRect();
            QPointF marioTopLeft = this->mapToScene(marioRect.topLeft());
            QPointF marioBottomRight = this->mapToScene(marioRect.bottomRight());

            //check colliding direction

            collidedTop = marioBottomRight.y() <= itemTopLeft.y();
            collidedBottom = marioTopLeft.y()-3 >= itemBottomRight.y();
            collidedLeft = marioBottomRight.x() <= itemTopLeft.x();
            collidedRight = marioTopLeft.x() >= itemBottomRight.x();
            qDebug() << marioBottomRight <<"; " << itemTopLeft;
            */

            }
    }
    qDebug() << "collideBottom:" <<collidedBottom << "; collideR:" << collidedRight << "; collideL:" << collidedLeft <<"; CollideTop:" <<collidedTop;
}




