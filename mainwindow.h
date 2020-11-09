#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace std;
class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString s2q(const string&);
    string q2s(const QString&);

private slots:
    void on_btn_submit_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
