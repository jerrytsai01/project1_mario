#ifndef FIREFLOWER_H
#define FIREFLOWER_H


#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsView>
class fireflower: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    fireflower(int x,int y,QGraphicsPixmapItem *parent = 0);
    void readview(QGraphicsView *view);
public slots:
    void flower_eaten_by_mario();
private:
    int x;
    int y;
};
#endif // FIREFLOWER_H
