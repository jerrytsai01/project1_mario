#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsSceneEvent>
#include <mario.h>
/*
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    ~MainWindow();
    mario *player;
private:
   // Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
