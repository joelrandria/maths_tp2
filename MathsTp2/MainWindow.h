#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionCloseApplication_triggered();
    void on_actionNewEdge_triggered();

    void on_lowPassFilterSlider_valueChanged(int value);
    void on_lowPassFilterSpinbox_valueChanged(double arg1);

private:

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
