#include "mainwindow.h"
#include "./ui_mainwindow.h"

static QString formatTimeDisplay(const int totalSeconds) {
    const int minutes = totalSeconds / 60;
    const int seconds = totalSeconds % 60;

    return QString("%1:%2")
            .arg(minutes, 2, 10, QChar('0'))
            .arg(seconds, 2, 10, QChar('0'));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
      , currentShortSeconds(0)
      , currentLongSeconds(0)
      , shortBreakDuration(60 * 5)
      , longBreakDuration(60 * 25)
      , isRunning(true) {
    ui->setupUi(this);
    breakTimer = new QTimer(this);

    initBreakBars();
    connect(breakTimer, &QTimer::timeout, this, &MainWindow::updateProgress);

    breakTimer->start(1000);
}

void MainWindow::initBreakBars() const {
    ui->shortBreakBar->setMaximum(shortBreakDuration);
    ui->longBreakBar->setMaximum(longBreakDuration);

    ui->shortBreakBar->setValue(0);
    ui->longBreakBar->setValue(0);

    ui->shortBreakBar->setFormat(formatTimeDisplay(currentShortSeconds));
    ui->longBreakBar->setFormat(formatTimeDisplay(currentShortSeconds));
}

void MainWindow::updateProgress() {
    currentShortSeconds++;
    currentLongSeconds++;

    ui->shortBreakBar->setValue(currentShortSeconds);
    ui->shortBreakBar->setFormat(formatTimeDisplay(currentShortSeconds));

    if (currentShortSeconds >= shortBreakDuration) {
        currentShortSeconds = 0;
    }

    ui->longBreakBar->setValue(currentLongSeconds);
    ui->longBreakBar->setFormat(formatTimeDisplay(currentLongSeconds));

    if (currentLongSeconds >= longBreakDuration) {
        currentLongSeconds = 0;
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
