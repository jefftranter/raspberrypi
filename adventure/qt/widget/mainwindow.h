#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QButtonGroup>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QLabel *locationLabel;
    QLabel *turnsLabel;
    QButtonGroup *objectButtonGroup;
    QButtonGroup *inventoryButtonGroup;
};

#endif // MAINWINDOW_H
