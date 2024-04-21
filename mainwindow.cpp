#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mario.h"
#include "bricks.h"
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QScrollBar>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

        setFixedSize(1400,600);
        setWindowTitle("SuperMario");
        // 創建場景
        QGraphicsScene *scene = new QGraphicsScene();
        scene->setSceneRect(0, 0, 7000, 600); // 設置場景大小為1400x600

        // 添加背景圖
        QPixmap background(":/new/prefix1/image/background.png");
        // 计算需要多少个背景图来填满场景的宽度
           int numTiles = 7000 / background.width() + 1;

           // 创建多个 QGraphicsPixmapItem 对象，并设置图片为背景图片
           for (int i = 0; i < numTiles; ++i) {
               QGraphicsPixmapItem *backgroundItem = new QGraphicsPixmapItem(background);
               // 设置每个 QGraphicsPixmapItem 对象的位置
               backgroundItem->setPos(i * background.width(), 0);
               // 将 QGraphicsPixmapItem 对象添加到场景中
               scene->addItem(backgroundItem);
           }

        // 添加地板磚塊
        QPixmap brickPixmap(":/new/prefix1/image/brick/floor brick.png");
        const int brickWidth = 50;
        const int numBricks = 7000 / brickWidth;
        for (int i = 0; i < numBricks; ++i) {
            if((i!=30) && (i!=31)){
                bricks *brickItem = new bricks(brickPixmap, i * brickWidth, 500);
                scene->addItem(brickItem); // 将砖块添加到场景中
            }
        }

        // 創建視圖並設置場景
        QGraphicsView *view = new QGraphicsView(scene);
        view->setFixedSize(1400, 600); // 設置視圖大小為1400x600
        view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 關閉水平滾動條
        view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 關閉垂直滾動條
        view->horizontalScrollBar()->setValue(0);

        //創建馬力歐
        mario * player = new mario();
        scene->addItem(player);
        player->readview(view);

        player->setFlag(QGraphicsItem::ItemIsFocusable);
        player->setFocus();

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

MainWindow::~MainWindow()
{
    delete ui;
}
