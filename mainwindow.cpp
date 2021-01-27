#include <opencv2/videoio/videoio.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <QMessageBox>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "converter.h"
#include "view.h"

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
{
  
    ui->setupUi(this);
    
    main_view = new my::widget::View();
    main_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    main_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->view_layout->addWidget(main_view);
   
    timer= new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
 
    capScene = new QGraphicsScene();
    imgScene = new QGraphicsScene();
   
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

    pixels->setPixmap(my::Converter::Mat2QPixmap(frame));
}


void MainWindow::on_open_camera_btn_clicked()
{
    if (!timer->isActive()) {
        cap.open(0);
        if (cap.isOpened()) {
            pixels = new QGraphicsPixmapItem();
            capScene->addItem(pixels);
            main_view->setScene(capScene);
            updateFrame();
            main_view->fitInView(pixels, Qt::KeepAspectRatio);
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
    frame = cv::imread(my::Converter::q2s(filePath), cv::IMREAD_COLOR);
    if (frame.empty())
    {
        QMessageBox::information(this, "Error", "Could not read the image: " + filePath);
        return;
    }
    pixels = new QGraphicsPixmapItem();
    pixels->setPixmap(my::Converter::Mat2QPixmap(frame));
    
    imgScene->addItem(pixels);
    main_view->setScene(imgScene);
    main_view->fitInView(pixels, Qt::KeepAspectRatio);

}

void MainWindow::on_reverseH_clicked()
{
    cv::flip(frame, frame, 1);   
    pixels->setPixmap(my::Converter::Mat2QPixmap(frame));
}

void MainWindow::on_reverseV_clicked()
{
    cv::flip(frame, frame, 0);
    pixels->setPixmap(my::Converter::Mat2QPixmap(frame));
}
