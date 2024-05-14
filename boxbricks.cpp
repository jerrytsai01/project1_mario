#include "boxbricks.h"
#include "mario.h"
#include"coin.h"
#include "supermushroom.h"
#include "fireflower.h"
#include <QGraphicsItem>
#include <QGraphicsScene>
#include<QTimer>

boxbricks::boxbricks(int x,int y,int item,QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent),x(x),y(y),item(item)
{
    setPixmap(QPixmap(":/new/prefix1/image/brick/box brick.png"));
    setPos(x,y);

    QTimer *timer =new QTimer(this);
    connect(timer,&QTimer::timeout,this,&boxbricks::touch);
    timer->start(5);
    connect(this, SIGNAL(touched()), this, SLOT(obj()));
}

void boxbricks::touch(){
    if(mario::colliedTopOBJ == this->pos()){
        emit touched();

        setPixmap(QPixmap(":/new/prefix1/image/brick/stone brick.png"));
    }
}
/*QList<QGraphicsItem*> collidingItems =scene()-> collidingItems(this, Qt::IntersectsItemBoundingRect);
for (int i =0;i<collidingItems.size();i++) {
    QGraphicsItem *item = collidingItems[i];
        if(typeid(*item) == typeid(mario)) {
            QPointF itemPos = item->pos();
            QRectF boundingRect = item->boundingRect();
            qreal itemw = boundingRect.width();
            qreal itemx = itemPos.x();
            qreal itemy = itemPos.y();
            if(itemx+itemw>=x and itemx<=x+50 and itemy <=y+50 and itemy >= y+47 and hit==0){
                emit touched();
                hit=1;
                setPixmap(QPixmap(":/new/prefix1/image/brick/stone brick.png"));
            }
        }
    }*/
void boxbricks::obj(){
    //coin
    if(hit){
        if(item==1){
            Coin::score++;
            if(Coin::scorelabel)
            Coin::scorelabel->setText("Score: " + QString::number(Coin::score));
            //coin
            Coin *coin= new Coin(x,y-60);
            int coinx=x;
            int coiny=y-60;
            scene()->addItem(coin);
            QTimer *timer = new QTimer(this);
            int count =0;
            connect(timer,&QTimer::timeout,this,[=]()mutable{
                count++;
                if(count ==1){
                    coin->setPos(coinx,coiny-5);
                    coiny=coiny-5;
                    timer->start(50);
                }
                else if(count ==2){
                    coin->setPos(coinx,coiny-3);
                    coiny=coiny-3;
                    timer->start(50);
                }
                else if(count ==3){
                    coin->setPos(coinx,coiny-1);
                    coiny=coiny-1;
                    timer->start(50);
                }
                else if(count ==4){
                    coin->setPos(coinx,coiny+1);
                    coiny=coiny+1;
                    timer->start(50);
                }
                else if(count ==5){
                    coin->setPos(coinx,coiny+3);
                    coiny=coiny+3;
                    timer->start(50);
                }
                else if(count ==6){
                    coin->setPos(coinx,coiny+5);
                    coiny=coiny+5;
                    timer->start(50);
                }
                else {
                    timer->stop();
                    scene()->removeItem(coin);
                    delete coin;
                    count =0;
                }
            });
            timer->start(10);
        }
        //supermushroom
        else if(item==2){
            supermushroom *mushroom = new supermushroom(x,y-50);
            scene()->addItem(mushroom);
        }
        //fireflower
        else if(item==3){
            fireflower *flower = new fireflower(x,y-50);
            scene()->addItem(flower);
        }
        hit=0;
    }
}
