#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>
#include <QMessageBox>
#include <QPixmap>
#include <QGraphicsPixmapItem>

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
{
  
    ui->setupUi(this);
    timer= new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateFrame()));

    pixels = new QGraphicsPixmapItem();
    capScene = new QGraphicsScene();
    ui->camera_view->setScene(capScene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_camera_btn_clicked()
{
    cap.open(0);
    if (cap.isOpened()) {
        pixels = new QGraphicsPixmapItem();
        capScene->addItem(pixels);
        timer->start(20);
    }
    else {
        QMessageBox::information(this, "Error message", "camera opened fail...");
    }
   
}

void MainWindow::on_close_camera_btn_clicked()
{
    timer->stop();
    cap.release();
    capScene->clear();
}

void MainWindow::updateFrame()
{
    cap.read(frame);

    if (!frame.data)
    {
        QMessageBox::information(this, "Error message", "cannot read frame..");
    }

    cvtColor(frame, frame, COLOR_BGR2RGB);
    pixels->setPixmap(QPixmap::fromImage(QImage((const unsigned char*)frame.data, frame.cols, frame.rows, frame.cols * frame.channels(), QImage::Format_RGB888)));
}

