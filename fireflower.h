#ifndef FIREFLOWER_H
#define FIREFLOWER_H


#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsView>
class fireflower: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    fireflower(QGraphicsPixmapItem *parent = 0);
    void readview(QGraphicsView *view);
public slots:
    void flower_eaten_by_mario();
};
#endif // FIREFLOWER_H
