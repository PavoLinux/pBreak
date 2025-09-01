#include "mainwindow.h"

#include <QTimer>

#include "./ui_mainwindow.h"

constexpr int INACTIVITY_TIMER_DURATION = 2000;
constexpr int BREAK_TIMER_DURATION = 1000;

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
    setFixedSize(size());
    breakTimer = new QTimer(this);

    initBreakBars();
    connect(breakTimer, &QTimer::timeout, this, &MainWindow::updateProgress);
    breakTimer->start(BREAK_TIMER_DURATION);

    inactivityTimer = new QTimer(this);
    connect(inactivityTimer, &QTimer::timeout, this, &MainWindow::checkMouseActivity);
    inactivityTimer->start(INACTIVITY_TIMER_DURATION);

    lastMousePos = QCursor::pos();
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

void MainWindow::checkMouseActivity() {
    if (const QPoint currentMousePos = QCursor::pos(); currentMousePos != lastMousePos) {
        lastMousePos = currentMousePos;

        if (!isRunning) {
            breakTimer->start(BREAK_TIMER_DURATION);
            isRunning = true;
        }

        inactivityTimer->start(INACTIVITY_TIMER_DURATION);
    } else if (isRunning) {
        breakTimer->stop();
        isRunning = false;
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
