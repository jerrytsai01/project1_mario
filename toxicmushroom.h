#ifndef TOXICMUSHROOM_H
#define TOXICMUSHROOM_H


#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsView>
class toxicmushroom: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public :
    toxicmushroom(QGraphicsPixmapItem *parent=0);
    void readview(QGraphicsView *view);
public slots:
    void toxicmushroom_move();
};


#endif // TOXICMUSHROOM_H
