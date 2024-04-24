#ifndef STONEBRICKS_H
#define STONEBRICKS_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsView>

class stonebricks: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    stonebricks(QGraphicsPixmapItem *parent=0);
};

#endif // STONEBRICKS_H
