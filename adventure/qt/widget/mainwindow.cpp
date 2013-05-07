#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{
    locationLabel = new QLabel(tr("Turns: 0"));
    turnsLabel = new QLabel(tr("Location: driveway"));
    statusBar()->addPermanentWidget(turnsLabel, 1);
    statusBar()->addPermanentWidget(locationLabel);

    // Signal/slot connections
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(quit()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit()));

    objectButtonGroup = new QButtonGroup();
    objectButtonGroup->addButton(ui->objectButton1, 0);
    objectButtonGroup->addButton(ui->objectButton2, 1);
    objectButtonGroup->addButton(ui->objectButton3, 2);
    objectButtonGroup->addButton(ui->objectButton4, 3);
    objectButtonGroup->addButton(ui->objectButton5, 4);
    objectButtonGroup->addButton(ui->objectButton6, 5);

    for (int i = 0; i < 6; ++i) {
        objectButtonGroup->button(i)->setText(tr("-"));
    }

    inventoryButtonGroup = new QButtonGroup();
    inventoryButtonGroup->addButton(ui->inventoryButton1, 0);
    inventoryButtonGroup->addButton(ui->inventoryButton2, 1);
    inventoryButtonGroup->addButton(ui->inventoryButton3, 2);
    inventoryButtonGroup->addButton(ui->inventoryButton4, 3);
    inventoryButtonGroup->addButton(ui->inventoryButton5, 4);

    for (int i = 0; i < 5; ++i) {
        inventoryButtonGroup->button(i)->setText(tr("-"));
    }

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

void MainWindow::quit()
{
    int button = QMessageBox::question(this, tr("Confirm Quit"), tr("Are you sure you want to quit?"));
    if (button == QMessageBox::Yes) {
        qApp->quit();
    }
}

void MainWindow::gameOver()
{
    int turns = 47;
    int button = QMessageBox::question(this, tr("Game Over"), tr("Game over after %1 turns.\nDo you want to play again?").arg(turns));
    if (button == QMessageBox::No) {
        qApp->quit();
    }
}

// This intercepts the window close so we can ask the user to confirm.
void MainWindow::closeEvent(QCloseEvent *event)
{
    quit();
    event->ignore(); // If we got here we do not want to quit.
}
