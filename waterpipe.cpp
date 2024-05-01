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

waterpipe::waterpipe(QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{
    setPixmap(QPixmap(":/new/prefix1/image/brick/water pipe.png"));
    setPos(300,400);
}
