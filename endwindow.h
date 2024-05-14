#ifndef ENDWINDOW_H
#define ENDWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QPushButton>

class endwindow : public QMainWindow{
    Q_OBJECT
public:
    endwindow(QWidget *parent = nullptr);
signals:
    void reset();

public slots:
    void gg();

private:
    QGraphicsScene *scene = new QGraphicsScene();
    QPushButton *playButton;
    QGraphicsView *view = new QGraphicsView(scene);
    QLabel *result = new QLabel();
};

#endif // ENDWINDOW_H
