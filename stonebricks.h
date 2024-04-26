#ifndef STONEBRICKS_H
#define STONEBRICKS_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsView>

class stonebricks: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    stonebricks(int x,int y,QGraphicsPixmapItem *parent=0);
};

#endif // STONEBRICKS_H
