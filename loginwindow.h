#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>

class loginwindow : public QMainWindow {
    Q_OBJECT
public:
    loginwindow(QWidget *parent = nullptr);

signals:
    void startGame();

private slots:
    void onPlayClicked();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPushButton *playButton;
};


#endif // LOGINWINDOW_H
