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
    createButton();
    int createButtonTime =
            QRandomGenerator::global()->
            bounded(createButtonTimeLowerLimit, createButtonTimeUpperLimit);
    QTimer::singleShot(createButtonTime, this, &MainWindow::recursiveCreateButtonTimeDelay);

}

void MainWindow::createButton()
{
    int x = QRandomGenerator::global()->bounded(this->width() - buttonSize.width());
    int y = QRandomGenerator::global()->bounded(moveHeightLimit - buttonSize.height());
    double animationTime = QRandomGenerator::global()->bounded(animationTimeLowerLimit, animationTimeUpperLimit);
    const double timerDuration = 5;
    const int finalYCorrd = this->height() - buttonSize.height();
    qInfo() << "finalYCoord = " << finalYCorrd;
    double defaultYShift = (finalYCorrd - y) * (timerDuration) / animationTime;
    qInfo() << defaultYShift;
    double underMouseYShift = 2 * defaultYShift;

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

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() mutable {
        QPushButton*& currentButton = this->buttonMap[currentKey];
        if (currentButton)
        {
            if (currentButton->pos().y() == (this->height() - buttonSize.height()))
            {
                qInfo() << "Game is lost!";
                this->setStyleSheet("background-color: red;");
                currentButton->deleteLater();
                timer->stop();
            }
            else if (currentButton->underMouse())
            {
                currentButton->move(x, currentButton->pos().y() + underMouseYShift);
            }
            else
            {
                currentButton->move(x, currentButton->pos().y() + defaultYShift);
            }
        }
    });
    timer->start(timerDuration);

    QObject::connect(button, &QPushButton::clicked, this, deleteButton);
}
