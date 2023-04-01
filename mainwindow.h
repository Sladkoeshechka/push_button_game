#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <map>
#include <QSize>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createButton();
    void recursiveCreateButtonTimeDelay();
    std::map <int, QPushButton*> buttonMap;
    int buttonKey = 0;

    const QSize buttonSize = QSize(20, 20);
    const uint32_t animationTimeLowerLimit = 25000;
    const uint32_t animationTimeUpperLimit = 50000;
    const int moveHeightLimit = 100;
    const uint32_t createButtonTimeLowerLimit = 100;
    const uint32_t createButtonTimeUpperLimit = 1000;
};
#endif // MAINWINDOW_H
