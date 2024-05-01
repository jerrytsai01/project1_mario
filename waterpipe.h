#ifndef WATERPIPE_H
#define WATERPIPE_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsView>
class waterpipe: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    waterpipe(QGraphicsPixmapItem *parent = 0);
    void readview(QGraphicsView *view);
};

#endif // WATERPIPE_H
