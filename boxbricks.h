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
private slots:
    void touch();
    void obj();

private:
    int x;
    int y;
    int item;
    bool hit=1;
};

#endif // BOXBRICKS_H
