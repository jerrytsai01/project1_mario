#ifndef ENDWINDOW_H
#define ENDWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>

class endwindow : public QMainWindow{
    Q_OBJECT
public:
    endwindow(QWidget *parent = nullptr);
signals:
    void reset();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QPushButton *playButton;


};

#endif // ENDWINDOW_H
