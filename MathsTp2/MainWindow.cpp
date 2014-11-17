#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "EdgeView.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCloseApplication_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionNewEdge_triggered()
{
    ui->edgeView->reset();

    ui->lowPassFilterSpinbox->setValue(0);
}

void MainWindow::on_lowPassFilterSlider_valueChanged(int value)
{
    ui->lowPassFilterSpinbox->setValue(value);
}
void MainWindow::on_lowPassFilterSpinbox_valueChanged(double arg1)
{
    ui->lowPassFilterSlider->setValue(arg1);

    ui->edgeView->applyLowPassFilter(arg1);
}
