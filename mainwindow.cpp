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
#include "converter.h"
#include "scene.h"

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
    
    //capScene = new QGraphicsScene();
    //capScene->addItem(pixels);

    imgScene = new myQT::Scene(ui->image_view);
    imgScene->addItem(pixels);

   
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

    pixels->setPixmap(Converter::Mat2QPixmap(frame));
}


void MainWindow::on_open_camera_btn_clicked()
{
    cap.open(0);
    if (cap.isOpened()) {
        ui->image_view->setScene(capScene);
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
    ui->image_view->setScene(imgScene);
    QString filePath = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files (*.png *.jpg)");
    frame = imread(Converter::q2s(filePath), IMREAD_COLOR);
    if (frame.empty())
    {
        QMessageBox::information(this, "Error message", "Could not read the image: " + filePath);
        return;
    }
    pixels->setPixmap(Converter::Mat2QPixmap(frame)); 
    ui->image_view->fitInView(pixels, Qt::KeepAspectRatio);
}