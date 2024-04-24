#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mario.h"
#include "floorbricks.h"
#include "stonebricks.h"
#include "toxicmushroom.h"

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
        QPixmap floorBrickPixmap(":/new/prefix1/image/brick/floor brick.png");
        const int brickWidth = 50;
        const int numBricks = 7000 / brickWidth;
        for (int i = 0; i < numBricks; ++i) {
            if(((i>=11)&&(i<=12)) || ((i>=35)&&(i<=45)) || ((i>=65)&&(i<=105))){
                continue;
            }
            else
            {
                floorBricks *floorBrickItem = new floorBricks(floorBrickPixmap, i * brickWidth, 500);
                scene->addItem(floorBrickItem); // add floor bricks into scene
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

        //create toxic mushroom

        toxicmushroom *mushroom = new toxicmushroom();
        scene->addItem(mushroom);

        // 定义磚塊的宽度和高度
        const int w = 50;
        const int h = 50;

        // 定义地图上磚塊的布局，这里只是一个示例，你可以根据实际需要修改
        QVector<QPointF> brickPositions = {
            QPointF(10*w, 5*h),
            QPointF(11*w, 5*h),
            QPointF(12*w, 5*h),
            QPointF(3*w, 8*h),
        };

        // 在每个位置上生成磚塊
        for (const QPointF& position : brickPositions) {
            stonebricks *brick = new stonebricks(position.x(), position.y());
            brick->setPixmap(QPixmap(":/new/prefix1/image/brick/stone brick.png"));
            brick->setPos(position);
            scene->addItem(brick);
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

MainWindow::~MainWindow()
{
    delete ui;
}

