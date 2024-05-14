#include "endwindow.h"
#include <QLabel>

endwindow::endwindow(QWidget *parent) : QMainWindow(parent){
    QGraphicsScene *scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1080, 600);
    scene->setBackgroundBrush(Qt::black);
    QGraphicsView *view = new QGraphicsView(scene);
    view->setFixedSize(1080, 600);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 關閉水平滾動條
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // 關閉垂直滾動條
    setCentralWidget(view);

    QLabel *Label = new QLabel("GAME OVER", view);
    Label->setStyleSheet("QLabel { color : white; font-size: 60px; }");
    Label->move(360,100);


    playButton = new QPushButton(view);
    playButton->setText("continue");
    playButton->setStyleSheet("font-size: 18px;");
    playButton->move((1080 - playButton->width()) / 2,454);

    connect(playButton, &QPushButton::clicked, this, &endwindow::reset);
    connect(playButton, &QPushButton::clicked, this, &QWidget::close);
}
