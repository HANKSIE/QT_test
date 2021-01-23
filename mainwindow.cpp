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

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
{
  
    ui->setupUi(this);

    ui->image_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->image_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    timer= new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
 
    capScene = new myQT::Scene(ui->image_view);
    imgScene = new myQT::Scene(ui->image_view);

    pixels = new QGraphicsPixmapItem();
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

    pixels->setPixmap(helper::Converter::Mat2QPixmap(frame));
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
    imgScene->clear();
    QString filePath = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files (*.png *.jpg)");
    frame = cv::imread(helper::Converter::q2s(filePath), cv::IMREAD_COLOR);
    if (frame.empty())
    {
        QMessageBox::information(this, "Error", "Could not read the image: " + filePath);
        return;
    }
    pixels = new QGraphicsPixmapItem();
    pixels->setPixmap(helper::Converter::Mat2QPixmap(frame));
    imgScene->addItem(pixels);
    ui->image_view->setScene(imgScene);
    ui->image_view->fitInView(pixels, Qt::KeepAspectRatio);
}