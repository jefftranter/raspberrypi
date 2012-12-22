#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    locationLabel = new QLabel(tr("Turns: 60"));
    turnsLabel = new QLabel(tr("Location: driveway"));
    statusBar()->addPermanentWidget(turnsLabel, 1);
    statusBar()->addPermanentWidget(locationLabel);

    ui->textEdit->setText(
"                        Abandoned Farmhouse Adventure\n"
"                                By Jeff Tranter\n"
"\n"
"Your three-year-old grandson has gone missing and was last seen headed in the\n"
"direction of the abandoned family farm. It's a dangerous place to play.\n"
"You have to find him before he gets hurt, and it will be getting dark soon...\n"
"? "
);

}

MainWindow::~MainWindow()
{
    delete ui;
}
