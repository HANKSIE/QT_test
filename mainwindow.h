#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <opencv2/videoio/videoio.hpp>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;
using namespace cv;

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_open_camera_btn_clicked();
    void on_close_camera_btn_clicked();

    void updateFrame();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    VideoCapture cap;
    Mat frame;
    QGraphicsScene *capScene;
    QGraphicsPixmapItem *pixels;
};
#endif // MAINWINDOW_H
