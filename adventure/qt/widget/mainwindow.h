#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QCloseEvent>
#include <QLabel>
#include <QMainWindow>

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
protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    QLabel *locationLabel;
    QLabel *turnsLabel;
    QButtonGroup *objectButtonGroup;
    QButtonGroup *inventoryButtonGroup;
};

#endif // MAINWINDOW_H
