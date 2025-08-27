#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateProgress();

private:
    Ui::MainWindow *ui;

    QTimer* breakTimer;
    int currentSeconds;
    int maxSeconds;
    bool isRunning;

    void updateTimeDisplay();
};
#endif // MAINWINDOW_H
