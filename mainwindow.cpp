#include "mainwindow.h"
#include <QPushButton>
#include <QSize>
#include <QRandomGenerator>
#include <QTimer>
#include <QPropertyAnimation>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(800, 1600);

    recursiveCreateButtonTimeDelay();
}

MainWindow::~MainWindow()
{

}

void MainWindow::recursiveCreateButtonTimeDelay()
{
    int animationTime = QRandomGenerator::global()->bounded(animationTimeLowerLimit, animationTimeUpperLimit);
    int x = QRandomGenerator::global()->bounded(this->width() - buttonSize.width());
    int y = QRandomGenerator::global()->bounded(moveHeightLimit - buttonSize.height());
    createButton(x, y, animationTime);
    int createButtonTime =
            QRandomGenerator::global()->
            bounded(createButtonTimeLowerLimit, createButtonTimeUpperLimit);
    QTimer::singleShot(createButtonTime, this, [=](){
        recursiveCreateButtonTimeDelay();
    });
}

void MainWindow::createButtonWithFasterAnimation(int x, int y, int animationTime)
{

}

void MainWindow::createButton(int x, int y, int animationTime)
{

    int currentKey = buttonKey++;
    buttonMap[currentKey] = new QPushButton(this);
    QPushButton *button = buttonMap[currentKey];

    QPixmap pixmap(10,10);
    pixmap.fill(QColor("black"));
    QIcon blackIcon(pixmap);
    button->setIcon(blackIcon);
    button->move(x, y);
    button->resize(buttonSize);
    button->show();

    auto deleteButton = [currentKey, this](){
        QPushButton*& currentButton = this->buttonMap[currentKey];
        currentButton->deleteLater();
        currentButton = nullptr;
    };

    QObject::connect(button, &QPushButton::clicked, this, deleteButton);

    QPropertyAnimation *animation = new QPropertyAnimation(button, "geometry");
    animation->setDuration(animationTime);
    animation->setStartValue(QRect(x, y, buttonSize.width(), buttonSize.height()));
    animation->setEndValue(QRect(x, this->height() - buttonSize.height(), buttonSize.width(), buttonSize.height()));
    animation->start();

    QTimer::singleShot(animationTime, this, [=](){
        if(buttonMap[currentKey]) {
            this->setStyleSheet("background-color: red;");
            qInfo() << "You are a dead man!";
            deleteButton();
        }
    });
}
