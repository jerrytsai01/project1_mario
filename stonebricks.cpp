#include "stonebricks.h"
#include "QGraphicsPixmapItem"
#include "mainwindow.h"
#include <QGraphicsScene>

stonebricks::stonebricks(QGraphicsPixmapItem *parent):QGraphicsPixmapItem (parent)
{
    setPixmap(QPixmap(":/new/prefix1/image/brick/stone brick.png"));
}

