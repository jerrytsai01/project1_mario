#include "normalbricks.h"
#include "mario.h"
#include "coin.h"
#include<QTimer>
#include <QList>
#include <QtDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QThread>

normalbricks::normalbricks(int x,int y,int coinsum,QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent),x(x),y(y),coinsum(coinsum)
{
    setPixmap(QPixmap(":/new/prefix1/image/brick/normal brick.png"));
    setPos(x,y);
    icoinsum=coinsum;
    QTimer *timer =new QTimer(this);
    connect(timer,&QTimer::timeout,this,&normalbricks::touch);
    timer->start(5);
    connect(this, SIGNAL(jump()), this, SLOT(bounce()));
    connect(this, SIGNAL(jump()), this, SLOT(getcoin()));
    connect(this, SIGNAL(cjump()), this, SLOT(coinjump()));
    if(coinsum>0){
        havecoin=1;
    }
    else {
        havecoin=0;
    }
}

void normalbricks::touch(){
    if(mario::colliedTopOBJ == this->pos()){
        // touch
        emit jump();
    }
}

void normalbricks::bounce(){
    //setPos(x,y-10);
    if(havecoin){
        if(coinsum>0){
            qDebug()<<"bounce";
            QTimer *timer = new QTimer(this);
            int count =0;
            connect(timer,&QTimer::timeout,this,[=]()mutable{
                count++;
                if(count ==1){
                    setPos(x,y-5);
                    y=y-5;
                    timer->start(50);
                }
                else if(count ==2){
                    setPos(x,y-3);
                    y=y-3;
                    timer->start(50);
                }
                else if(count ==3){
                    setPos(x,y-1);
                    y=y-1;
                    timer->start(50);
                }
                else if(count ==4){
                    setPos(x,y+1);
                    y=y+1;
                    timer->start(50);
                }
                else if(count ==5){
                    setPos(x,y+3);
                    y=y+3;
                    timer->start(50);
                }
                else if(count ==6){
                    setPos(x,y+5);
                    y=y+5;
                    timer->start(50);
                }
                else {
                    timer->stop();
                    count =0;
                }
            });
            timer->start(10);
        }
    }
    else{
        QTimer *timer = new QTimer(this);
        int count =0;
        connect(timer,&QTimer::timeout,this,[=]()mutable{
            count++;
            if(count ==1){
                setPos(x,y-5);
                y=y-5;
                timer->start(50);
            }
            else if(count ==2){
                setPos(x,y-3);
                y=y-3;
                timer->start(50);
            }
            else if(count ==3){
                setPos(x,y-1);
                y=y-1;
                timer->start(50);
            }
            else if(count ==4){
                setPos(x,y+1);
                y=y+1;
                timer->start(50);
            }
            else if(count ==5){
                setPos(x,y+3);
                y=y+3;
                timer->start(50);
            }
            else if(count ==6){
                setPos(x,y+5);
                y=y+5;
                timer->start(50);
            }
            else {
                timer->stop();
                count =0;
            }
        });
        timer->start(10);
    }
}

void normalbricks::getcoin(){
    if(havecoin){
        if(coinsum>0){
            emit cjump();
        }
        if(coinsum==0){
            setPixmap(QPixmap(":/new/prefix1/image/brick/stone brick.png"));
        }
    }
}

void normalbricks::coinjump(){
    Coin::score++;
    if(Coin::scorelabel)
    Coin::scorelabel->setText("Score: " + QString::number(Coin::score));
    coinsum--;
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

void normalbricks::reset(){
    coinsum=icoinsum;
    setPixmap(QPixmap(":/new/prefix1/image/brick/normal brick.png"));
}
