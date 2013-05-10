#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QCloseEvent>
#include <QLabel>
#include <QMainWindow>
#include "gameengine.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initialize();

public slots:
    void quit();
    void gameOver();
    void take();
    void drop();
    void use();
    void examine();
    void updateWindow(QString s);
    void updateTurns(int);
    void updateLocation(QString location);
    void updateInventoryItems(QStringList);
    void updateLocalItems(QStringList);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QLabel *locationLabel;
    QLabel *turnsLabel;
    QButtonGroup *objectButtonGroup;
    QButtonGroup *inventoryButtonGroup;
    GameEngine *e;
};

#endif // MAINWINDOW_H
