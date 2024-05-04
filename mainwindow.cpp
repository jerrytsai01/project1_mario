#include "mainwindow.h"
#include "ui_mainwindow.h"
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
        {16*w,9*h}
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
        {14*w,9*h-20}
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
    for(int i=1;i<10;i++){
        Coin *coin = new Coin(200*i,200);
        scene->addItem(coin);
    }

    // 添加地板磚塊
    QPixmap floorBrickPixmap(":/new/prefix1/image/brick/floor brick.png");
    const int floorbrickWidth = 50;
    const int numBricks = 7000 / floorbrickWidth;
    for (int i = 0; i < numBricks; ++i) {
        if(//floor hole postition
                /*((i>=11)&&(i<=11)) || ((i>=35)&&(i<=45)) || ((i>=65)&&(i<=75))*/
           0){
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
        {10*w,7*h},{11*w,7*h},
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
        {9*w,7*h},{8*w,7*h}
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
        {5*w,7*h},{6*w,7*h}
    };
    for (size_t i = 0; i < normalbrickpos.size(); i ++) {
        int x = normalbrickpos[i][0];
        int y = normalbrickpos[i][1];
        normalbricks *normalbrick = new normalbricks(x, y,30/*coins*/);

        scene->addItem(normalbrick);
    }

    //boxbricks
    std::vector<std::vector<int>> boxbrickpos={
        //brick position
        {10*w,7*h},{11*w,7*h}
    };
    for (size_t i = 0; i < boxbrickpos.size(); i ++) {
        int x = boxbrickpos[i][0];
        int y = boxbrickpos[i][1];
        boxbricks *boxbrick = new boxbricks(x, y,3/*1for coin 2for mushroom 3for flower*/);
        scene->addItem(boxbrick);
    }

    // 將視圖設置為主視窗的中央窗口
    setCentralWidget(view);
    /*// 创建定时器对象
                QTimer *timer = new QTimer(this);
                // 连接定时器的 timeout() 信号到 lockview() 槽函数
                connect(timer, &QTimer::timeout, this, [=]() {
                    player->lockview(view);
                });ss
                // 设置定时器的间隔时间，单位为毫秒
                int interval = 1; // 设置为 100 毫秒，即每隔 100 毫秒调用一次 lockview() 函数
                timer->start(interval);*/

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



