#ifndef SUPERMUSHROOM_H
#define SUPERMUSHROOM_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsView>
class supermushroom: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    supermushroom(QGraphicsPixmapItem *parent = 0);
    void readview(QGraphicsView *view);
public slots:
    void eaten_by_mario();
    void supermushroom_move();
};

#endif // SUPERMUSHROOM_H

