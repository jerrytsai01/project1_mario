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
    void setTargetPosition(const QPointF &target, const QPointF &start);

public slots:
    //void shot_by_mario(bool faceRight);
    void hit_the_toxicmushroom();
    void hit_the_bricks();
    void move();
private:
    qreal angle;
    qreal speed;
};

#endif // BULLET_H
