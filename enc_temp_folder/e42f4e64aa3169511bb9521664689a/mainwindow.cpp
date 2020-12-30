#include <opencv2/videoio/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <QImage>
#include <QMessageBox>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "converter.h";

using namespace cv;
using namespace helper;

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
{
  
    ui->setupUi(this);
    timer= new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateFrame()));

    pixels = new QGraphicsPixmapItem();
    capScene = new QGraphicsScene();
    imgScene = new QGraphicsScene();
    ui->image_view->setScene(capScene);
    ui->image_view->setScene(imgScene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateFrame()
{
    cap.read(frame);

    if (!frame.data)
    {
        QMessageBox::information(this, "Error message", "cannot read frame..");
    }

    //pixels->setPixmap(Converter::Mat2QPixmap(frame));
    cvtColor(frame, frame, COLOR_BGR2RGB);
    pixels->setPixmap(QPixmap::fromImage(QImage((const unsigned char*)frame.data, frame.cols, frame.rows, frame.cols * frame.channels(), QImage::Format_RGB888)));
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


void MainWindow::on_open_img_btn_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files (*.png *.jpg)");
    frame = imread(Converter::q2s(filePath), IMREAD_COLOR);
    if (frame.empty())
    {
        QMessageBox::information(this, "Error message", "Could not read the image: " + filePath);
        return;
    }
    pixels = new QGraphicsPixmapItem();
    pixels->setPixmap(Converter::Mat2QPixmap(frame));
    imgScene->addItem(pixels);
    imgScene->setSceneRect(ui->image_view->sceneRect());
   
}

