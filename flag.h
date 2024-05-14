#ifndef FLAG_H
#define FLAG_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsView>

class flag: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    flag(QGraphicsPixmapItem *parent = 0);

};

#endif // FLAG_H
