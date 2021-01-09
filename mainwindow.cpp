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
 
    capScene = new myQT::Scene(ui->image_view);
    imgScene = new myQT::Scene(ui->image_view);
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
        QMessageBox::information(this, "Error", "Cannot read frame. Camera turned off...");
        this->on_close_camera_btn_clicked();
        return;
    }

    pixels->setPixmap(Converter::Mat2QPixmap(frame));
}


void MainWindow::on_open_camera_btn_clicked()
{
    if (!timer->isActive()) {
        cap.open(0);
        if (cap.isOpened()) {
            pixels = new QGraphicsPixmapItem();
            capScene->addItem(pixels);
            ui->image_view->setScene(capScene);
            updateFrame();
            ui->image_view->fitInView(pixels, Qt::KeepAspectRatio);
            timer->start(20);
        }
        else {
            QMessageBox::information(this, "Error", "Camera failed to turn on ...");
        }
    }
    else {
        QMessageBox::information(this, "Error", "Camera turned on");
    }
}

void MainWindow::on_close_camera_btn_clicked()
{
    capScene->clear();
    timer->stop();
    cap.release();
}


void MainWindow::on_open_img_btn_clicked()
{
    this->on_close_camera_btn_clicked();
    pixels = new QGraphicsPixmapItem();
    imgScene->addItem(pixels);
    ui->image_view->setScene(imgScene);
    QString filePath = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files (*.png *.jpg)");
    frame = imread(Converter::q2s(filePath), IMREAD_COLOR);
    if (frame.empty())
    {
        QMessageBox::information(this, "Error", "Could not read the image: " + filePath);
        return;
    }
    pixels->setPixmap(Converter::Mat2QPixmap(frame)); 
    ui->image_view->fitInView(pixels, Qt::KeepAspectRatio);
}