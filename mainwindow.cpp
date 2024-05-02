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
    hpLabel->move(200,0);
    mario::hplabel=hpLabel;

    //create toxic mushroom
    toxicmushroom *mushroom1 = new toxicmushroom();
    scene->addItem(mushroom1);

    //create super mushroom
    supermushroom *supermushroom1 = new supermushroom();
    scene->addItem(supermushroom1);

    //create fire flower
    fireflower *fireflower1 = new fireflower();
    scene->addItem(fireflower1);

    //create waterpipe
    waterpipe *waterpipe1 = new waterpipe();
    scene->addItem(waterpipe1);

    //creat final flag
    flag *Flag = new flag();
    scene ->addItem(Flag);
    flag_pole *flagPole = new flag_pole();
    scene->addItem(flagPole);

    //score and coin
    Coin::score = 0;
    QLabel *scoreLabel = new QLabel("Score: 0", view);
    scoreLabel->setStyleSheet("QLabel { color : red; font-size: 45px; }");
    scoreLabel->move(0,0);
    Coin::scorelabel = scoreLabel;
    for(int i=1;i<10;i++){
        Coin *coin = new Coin(200*i,400);
        scene->addItem(coin);
    }

    // 添加地板磚塊
    QPixmap floorBrickPixmap(":/new/prefix1/image/brick/floor brick.png");
    const int floorbrickWidth = 50;
    const int numBricks = 7000 / floorbrickWidth;
    for (int i = 0; i < numBricks; ++i) {
        if(((i>=11)&&(i<=12)) || ((i>=35)&&(i<=45)) || ((i>=65)&&(i<=75))){
            continue;
        }
        else
        {
            floorBricks *floorBrickItem = new floorBricks(floorBrickPixmap, i * floorbrickWidth, 500);
            scene->addItem(floorBrickItem); // add floor bricks into scene
        }
    }

    // brick's height and weight
    const int w= 50;
    const int h = 50;

    //stone建構
    std::vector<std::vector<int>> stonebrickpos={
        {10*w,7*h},{11*w,7*h},{136*w,9*h}  //stone position
    };
    for (size_t i = 0; i < stonebrickpos.size(); i ++) {
        int x = stonebrickpos[i][0];
        int y = stonebrickpos[i][1];
        stonebricks *brick = new stonebricks(x, y);
        scene->addItem(brick);
    }

    //brokenrock
    std::vector<std::vector<int>> brokenbrickpos={
        {9*w,7*h},{8*w,7*h},{9*w,6*h},{8*w,6*h}  //stone position
    };
    for (size_t i = 0; i < brokenbrickpos.size(); i ++) {
        int x = brokenbrickpos[i][0];
        int y = brokenbrickpos[i][1];
        brokenbricks *brokenbrick = new brokenbricks(x, y);
        scene->addItem(brokenbrick);
    }

    // 將視圖設置為主視窗的中央窗口
    setCentralWidget(view);
    /*// 创建定时器对象
                QTimer *timer = new QTimer(this);
                // 连接定时器的 timeout() 信号到 lockview() 槽函数
                connect(timer, &QTimer::timeout, this, [=]() {
                    player->lockview(view);
                });
                // 设置定时器的间隔时间，单位为毫秒
                int interval = 1; // 设置为 100 毫秒，即每隔 100 毫秒调用一次 lockview() 函数
                timer->start(interval);*/

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

