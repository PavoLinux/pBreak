#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentSeconds()
    , maxSeconds(300)
    , isRunning(true)
{
    ui->setupUi(this);

    breakTimer = new QTimer(this);
    connect(breakTimer, &QTimer::timeout, this, &MainWindow::updateProgress);
    ui->shortBreakBar->setMinimum(0);
    ui->shortBreakBar->setMaximum(maxSeconds);
    ui->shortBreakBar->setValue(0);
    ui->shortBreakBar->setValue(0);
    ui->shortBreakBar->setFormat("%v / %m seconds (%p%)");

    updateTimeDisplay();
    breakTimer->start(1000);
}

void MainWindow::updateProgress()
{
    currentSeconds++;

    ui->shortBreakBar->setValue(currentSeconds);

    if (currentSeconds >= maxSeconds) {
        currentSeconds = 0;
        ui->shortBreakBar->setValue(0);
    }
}

void MainWindow::updateTimeDisplay()
{
    int minutes = currentSeconds / 60;
    int seconds = currentSeconds % 60;

    // ui->
}

MainWindow::~MainWindow()
{
    delete ui;
}
