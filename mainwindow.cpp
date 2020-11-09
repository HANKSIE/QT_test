#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "person.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
    QGraphicsScene *scene = new QGraphicsScene();
    scene->addEllipse( 0, 0, 100, 20 );
    scene->addRect(QRectF(0, 0, 100, 100));
    ui->g_view->setScene(scene);
    */


    /*
    QGraphicsScene scene;
    scene.addEllipse( 0, 0, 100, 20 );
    scene.addRect(QRectF(0, 0, 100, 100));
    ui->g_view->setScene(&scene);
    */

}

MainWindow::~MainWindow()
{
    delete ui;
}

// 將 string 轉換成 QString
QString MainWindow::s2q(const string &s) {
    return QString(QString::fromLocal8Bit(s.c_str()));
}

// 將 QString 轉換成 string
string MainWindow::q2s(const QString &s) {
     return string(static_cast<const char*>(s.toLocal8Bit()));
}

void MainWindow::on_btn_submit_clicked()
{
    string name =q2s(ui->te_name->toPlainText());
    int age = atoi(q2s(ui->te_age->toPlainText()).c_str());
    Person *p = new Person(name, age);
    ui->label_show->setText(s2q(p->intro()));
}
