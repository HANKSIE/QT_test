#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <QMessageBox>
#include <QFileDialog>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "converter.h"
#include "view.h"

#include "processExecutor.h"
#include "flip.h"


MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
{
  
    ui->setupUi(this);
    
    main_view = new my::widget::View();
    main_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    main_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ui->view_layout->addWidget(main_view);


    my::ProcessExecutor<cv::Mat> executor;
    my::Flip* fH = new my::Flip(1);
    my::Flip* fV = new my::Flip(0);
    executor.insert("flipH", fH);
    executor.insert("flipV", fV);
    imageSceneContext = new my::ImageSceneContext(executor);

    cameraSceneContext = new my::CameraSceneContext(executor);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_camera_btn_clicked()
{
    if (cameraSceneContext->open()) {
        currScene = Scene::CAMERA;
        imageSceneContext->close();
        main_view->setScene(cameraSceneContext);
        main_view->fitInView(cameraSceneContext->getPixels(), Qt::KeepAspectRatio);
    }
    else {
        QMessageBox::information(this, "Error", "Cannot turn on camera");
    }
   
}

void MainWindow::on_close_camera_btn_clicked()
{
    currScene = Scene::NONE;
    cameraSceneContext->close();
}

void MainWindow::on_open_img_btn_clicked()
{
    currScene = Scene::IMAGE;
    QString filePath = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files (*.png *.jpg)");
    if (imageSceneContext->open(my::Converter::q2s(filePath))) {
        main_view->setScene(imageSceneContext);
        main_view->fitInView(imageSceneContext->getPixels(), Qt::KeepAspectRatio);
        cameraSceneContext->close();
    }
}

void MainWindow::on_reverseH_clicked()
{
    if (currScene == Scene::CAMERA) {
        cameraSceneContext->executor.process("flipH")->turn();
    }

    if (currScene == Scene::IMAGE) {
        imageSceneContext->executor.process("flipH")->turn();
    }
}

void MainWindow::on_reverseV_clicked()
{
    if (currScene == Scene::CAMERA) {
        cameraSceneContext->executor.process("flipV")->turn();
    }

    if (currScene == Scene::IMAGE) {
        imageSceneContext->executor.process("flipV")->turn();
    }
}
