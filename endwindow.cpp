#include "endwindow.h"
#include "mario.h"
#include "coin.h"
#include <QLabel>

endwindow::endwindow(QWidget *parent) : QMainWindow(parent){

    scene->setSceneRect(0, 0, 1080, 600);
    scene->setBackgroundBrush(Qt::black);

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

void endwindow::gg(){

    if(mario::faliure ==1 or Coin::score <20){
        result->setText("YOU LOSE");
    }
    else if(Coin::score ==40){
        result->setText("Damn!!!");
    }
    else {
        result->setText("YOU WIN");
    }
    result->setStyleSheet("QLabel { color : black; font-size: 60px; }");
    result->move(370,250);
    scene->addWidget(result);

}
