#include "waterpipe.h"
#include "mainwindow.h"
#include <QKeyEvent>
#include <QDebug>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QList>

waterpipe::waterpipe(int x,int y,QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent),x(x),y(y)
{
    setPixmap(QPixmap(":/new/prefix1/image/brick/water pipe.png"));
    setPos(x,y);
}
