#include "loginwindow.h"
#include <QPixmap>


loginwindow::loginwindow(QWidget *parent) : QMainWindow(parent) {
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1080, 600);
    QGraphicsView *view = new QGraphicsView(scene);
    view->setFixedSize(1080, 600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 關閉水平滾動條
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 關閉垂直滾動條
    QPixmap backgroundImage(":/new/prefix1/image/start_screen.png");
    scene->addPixmap(backgroundImage);


    // 创建按钮并设置样式
    playButton = new QPushButton(view);
    playButton->setIcon(QIcon(":/new/prefix1/image/start_btn.png"));
    playButton->setFixedSize(196,46);
    playButton->setIconSize(playButton->size());
    playButton->move(530-98,454);

    setCentralWidget(view);


    // 连接按钮的点击事件到槽函数
    connect(playButton, &QPushButton::clicked, this, &loginwindow::onPlayClicked);
    connect(playButton, &QPushButton::clicked, this, &QWidget::close);
   }

void loginwindow::onPlayClicked() {
    // 发射开始游戏的信号
    emit startGame();
}
