#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsView>
class bullet:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    bullet(QGraphicsPixmapItem *parent = 0);
    void readview(QGraphicsView *view);
public slots:
    void shot_by_mario(bool faceRight);
    void hit_the_toxicmushroom();
    void hit_the_bricks();
};

#endif // BULLET_H
