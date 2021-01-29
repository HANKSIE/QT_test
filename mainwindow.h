#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <opencv2/videoio/videoio.hpp>

#include <QDialog>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "view.h"
#include "imageSceneContext.h"
#include "cameraSceneContext.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    enum class Scene
    {
        NONE, IMAGE, CAMERA
    };
    enum class Mode
    {
        DRAG, LINE
    };

    Scene currScene = Scene::NONE;
    Mode mode = Mode::DRAG;

public slots:
    void on_open_camera_btn_clicked();
    void on_close_camera_btn_clicked();
    void on_open_img_btn_clicked();
    void on_reverseH_clicked();
    void on_reverseV_clicked();

private:
    Ui::MainWindow *ui;
    my::widget::View* main_view;
    my::ImageSceneContext* imageSceneContext;
    my::CameraSceneContext* cameraSceneContext;
    
};
#endif // MAINWINDOW_H
