#include "mainwindow.h"
#include "mario.h"
#include "floorbricks.h"
#include "stonebricks.h"
#include "brokenbricks.h"
#include "boxbricks.h"
#include "normalbricks.h"
#include "toxicmushroom.h"
#include "supermushroom.h"
#include "fireflower.h"
#include "waterpipe.h"
#include "bullet.h"
#include "coin.h"
#include "flag.h"
#include "flag_pole.h"
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QScrollBar>
#include <QTimer>
#include <QDebug>
#include<vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1400,600);
    setWindowTitle("SuperMario");
    // 創建場景
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 7000, 600); // 設置場景大小為1400x600

    // 添加背景圖
    QPixmap background(":/new/prefix1/image/background.png");
    int numTiles = 7000 / background.width() + 1;
    // create QGraphicsPixmapItem and set as background
    for (int i = 0; i < numTiles; ++i) {
        QGraphicsPixmapItem *backgroundItem = new QGraphicsPixmapItem(background);
        // set the position and add
        backgroundItem->setPos(i * background.width(), 0);
        scene->addItem(backgroundItem);
        setStyleSheet("background: transparent;");
    }

    // 創建視圖並設置場景
    QGraphicsView *view = new QGraphicsView(scene);
    view->setInteractive(true);
    view->setFixedSize(1400, 600); // 設置視圖大小為1400x600
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 關閉水平滾動條
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 關閉垂直滾動條
    view->horizontalScrollBar()->setValue(0);
    //view->setBackgroundBrush(Qt::transparent);
    //view->setFocusPolicy(Qt::NoFocus);

    //創建馬力歐
    player = new mario();
    scene->addItem(player);
    player->readview(view);
    player->setFocus();
    mario::hp=3;
    QLabel *hpLabel = new QLabel("HP: 3",view);
    hpLabel->setStyleSheet("QLabel { color : red; font-size: 45px; }");
    hpLabel->move(400,0);
    mario::hplabel=hpLabel;


    // brick's height and weight
    const int w= 50;
    const int h = 50;

    //create toxic mushroom
    std::vector<std::vector<int>> mushroompos={
        //position
        {80*w,9*h},{98*w,9*h},{99*w,9*h},{100*w,9*h}
    };
    for (size_t i = 0; i < mushroompos.size(); i ++) {
        int x = mushroompos[i][0];
        int y = mushroompos[i][1];
        toxicmushroom *mushroom = new toxicmushroom(x, y);
        scene->addItem(mushroom);
    }


    //create waterpipe  high70
    std::vector<std::vector<int>> pipepos={
        //position
        {33*w,9*h-20},{64*w,9*h-20},{68*w,9*h-20},{88*w,9*h-20}
    };
    for (size_t i = 0; i < pipepos.size(); i ++) {
        int x = pipepos[i][0];
        int y = pipepos[i][1];
        waterpipe *pipe = new waterpipe(x, y);
        scene->addItem(pipe);
    }

    //creat final flag
    flag_pole *flagPole = new flag_pole();
    scene->addItem(flagPole);

    //score and coin
    Coin::score = 0;
    QLabel *scoreLabel = new QLabel("Score: 00", view);
    scoreLabel->setStyleSheet("QLabel { color : red; font-size: 45px; }");
    scoreLabel->move(0,0);
    Coin::scorelabel = scoreLabel;
    std::vector<std::vector<int>> coinpos={
        //coin position
        {6*w,7*h},{19*w,7*h},{20*w,7*h},{28*w,4*h},{50*w,6*h},{51*w,6*h},{50*w,3*h},{51*w,3*h},{60*w,3*h},{88*w,2*h},
        {99*w,6*h},{100*w,6*h},{101*w,6*h},{98*w,3*h},{99*w,3*h},{100*w,3*h},{101*w,3*h},{102*w,3*h},
        {108*w,7*h},{109*w,6*h},{110*w,7*h}
    };
    for (size_t i = 0; i < coinpos.size(); i ++) {
        int x = coinpos[i][0];
        int y = coinpos[i][1];
        Coin *coin = new Coin(x, y);
        scene->addItem(coin);
    }

    // floorbrick
    QPixmap floorBrickPixmap(":/new/prefix1/image/brick/floor brick.png");
    const int floorbrickWidth = 50;
    const int numBricks = 7000 / floorbrickWidth;
    for (int i = 0; i < numBricks; ++i) {
        if(//floor hole postition
                ((i>=19)&&(i<=20)) || ((i>=35)&&(i<=38)) || ((i>=66)&&(i<=67)) || ((i>=90)&&(i<=91))
           ){
            continue;
        }
        else
        {
            floorBricks *floorBrickItem = new floorBricks(floorBrickPixmap, i * floorbrickWidth, 500);
            scene->addItem(floorBrickItem); // add floor bricks into scene
        }
    }

    //stone建構
    std::vector<std::vector<int>> stonebrickpos={
        //stone position
        {36*w,7*h},{37*w,7*h},{41*w,5*h},{42*w,5*h},{43*w,5*h},{46*w,4*h},
        {81*w,5*h},{82*w,5*h},{83*w,5*h},{82*w,4*h},{83*w,4*h},{83*w,3*h},
        {97*w,7*h},{98*w,7*h},{99*w,7*h},{100*w,7*h},{101*w,7*h},{102*w,7*h},{103*w,7*h},
        {98*w,4*h},{99*w,4*h},{100*w,4*h},{101*w,4*h},{102*w,4*h},
        {116*w,9*h},{117*w,9*h},{118*w,9*h},{117*w,8*h},
        //flag state
        {128*w,9*h},{129*w,9*h},{130*w,9*h},{131*w,9*h},{132*w,9*h},{133*w,9*h},{129*w,8*h},{130*w,8*h},{131*w,8*h},{132*w,8*h},{133*w,8*h},{130*w,7*h},{131*w,7*h},{132*w,7*h},{133*w,7*h},{131*w,6*h},{132*w,6*h},{133*w,6*h},{132*w,5*h},{133*w,5*h},{133*w,4*h},
        {136*w,9*h}  //flag brick position

    };
    for (size_t i = 0; i < stonebrickpos.size(); i ++) {
        int x = stonebrickpos[i][0];
        int y = stonebrickpos[i][1];
        stonebricks *brick = new stonebricks(x, y);
        scene->addItem(brick);
    }

    //brokenrock
    std::vector<std::vector<int>> brokenbrickpos={
        //brick position
        {49*w,5*h},{49*w,6*h},{49*w,7*h},{50*w,5*h},{50*w,7*h},{51*w,5*h},{51*w,7*h},{52*w,7*h},{52*w,6*h},{52*w,5*h},
        {56*w,7*h},{55*w,7*h},{56*w,6*h},{55*w,6*h},{59*w,6*h},{60*w,6*h},{61*w,6*h},{60*w,5*h},{60*w,4*h}
    };
    for (size_t i = 0; i < brokenbrickpos.size(); i ++) {
        int x = brokenbrickpos[i][0];
        int y = brokenbrickpos[i][1];
        brokenbricks *brokenbrick = new brokenbricks(x, y);
        scene->addItem(brokenbrick);
    }

    //normalbricks
    std::vector<std::vector<int>> normalbrickpos={
        //brick position
        {11*w,3*h},{117*w,5*h},{10*w,7*h},{11*w,7*h},{12*w,7*h},{27*w,7*h},{29*w,7*h}
        ,{74*w,5*h},{75*w,7*h},{76*w,5*h},{73*w,8*h},{74*w,8*h},{76*w,8*h},{77*w,8*h},{78*w,8*h},{72*w,8*h},{78*w,9*h},{72*w,9*h}
    };
    for (size_t i = 0; i < normalbrickpos.size(); i ++) {
        int x = normalbrickpos[i][0];
        int y = normalbrickpos[i][1];
        if(i<2){
            normalbricks *normalbrick = new normalbricks(x, y,i+1/*coins*/);
            scene->addItem(normalbrick);
        }
        else{
            normalbricks *normalbrick = new normalbricks(x, y,0/*coins*/);
            scene->addItem(normalbrick);
        }
    }

    //boxbricks
    std::vector<std::vector<int>> boxbrickpos={
        //brick position
        {28*w,7*h},{75*w,5*h},{75*w,2*h}
    };
    for (size_t i = 0; i < boxbrickpos.size(); i ++) {
        int x = boxbrickpos[i][0];
        int y = boxbrickpos[i][1];
        boxbricks *boxbrick = new boxbricks(x, y,i%3+1/*1for coin 2for mushroom 3for flower*/);
        scene->addItem(boxbrick);
    }

    // 將視圖設置為主視窗的中央窗口
    setCentralWidget(view);

    // find max z value and assign to mario
    QList<QGraphicsItem*> items = scene->items();
    qreal maxZValue = std::numeric_limits<qreal>::min();
    for (QGraphicsItem *item : items) {
        qreal z = item->zValue();
        if (z > maxZValue) {
            maxZValue = z;
        }
    }
    player->setZValue(maxZValue);

    QTimer*colTimer = new QTimer(this);
    connect(colTimer, SIGNAL(timeout()), this, SLOT(player->coll));
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    qDebug() << "Mouse Pressed at: " << event->pos();
    QMainWindow::mousePressEvent(event); // 確保事件繼續向上傳遞
    player->fireEvent(event->pos());
    player->setFocus();
}

MainWindow::~MainWindow()
{
    //delete ui;
}



