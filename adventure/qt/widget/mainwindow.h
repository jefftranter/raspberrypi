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
    void commandOnItem(QAbstractButton *button);
    void updateWindow(QString msg);
    void updateTurns(int turns);
    void updateLocation(QString location);
    void updateInventoryItems(QStringList items);
    void updateLocalItems(QStringList items);
    void updateValidDirections(QStringList moves);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QLabel *m_locationLabel;
    QLabel *m_turnsLabel;
    QLabel *m_directionsLabel;
    QButtonGroup *m_objectButtonGroup;
    QButtonGroup *m_inventoryButtonGroup;
    GameEngine *m_game;
};

#endif // MAINWINDOW_H
