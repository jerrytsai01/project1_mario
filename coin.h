#ifndef COIN_H
#define COIN_H
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QLabel>

class Coin :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Coin(int x,int y,QGraphicsPixmapItem *parent=0);
    static int score;
    static QLabel *scorelabel;


signals:
    void collected();
private slots:
    void touch();
    void getcoin();

};

#endif // COIN_H
