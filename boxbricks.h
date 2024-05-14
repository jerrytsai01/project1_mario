#ifndef BOXBRICKS_H
#define BOXBRICKS_H
#include <QGraphicsPixmapItem>
#include<QObject>

class boxbricks: public QObject, public QGraphicsPixmapItem
{
     Q_OBJECT
public:
    boxbricks(int x,int y,int item,QGraphicsPixmapItem *parent=0);

signals:
    void touched();
public slots:
    void touch();
    void obj();
    void reset();

private:
    int x;
    int y;
    int item;
    bool hit=1;
};

#endif // BOXBRICKS_H
