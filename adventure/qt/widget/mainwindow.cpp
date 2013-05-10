/*
 * 
 * The Abandoned Farm House Adventure
 *
 * Jeff Tranter <tranter@pobox.com>
 *
 * Copyright 2012-1013 Jeff Tranter
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <QDebug>
#include <QButtonGroup>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameengine.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    e = new GameEngine;
    initialize();
}

MainWindow::~MainWindow()
{
    delete e;
    delete ui;
}

void MainWindow::initialize()
{
    locationLabel = new QLabel();
    turnsLabel = new QLabel();
    statusBar()->addPermanentWidget(turnsLabel, 1);
    statusBar()->addPermanentWidget(locationLabel);

    // Signal/slot connections
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit()));
    connect (e, SIGNAL(sendOutput(QString)), this, SLOT(updateWindow(QString)));
    connect (e, SIGNAL(updateLocation(QString)), this, SLOT(updateLocation(QString)));
    connect (e, SIGNAL(updateTurns(int)), this, SLOT(updateTurns(int)));
    connect (e, SIGNAL(updateInventoryItems(QStringList)), this, SLOT(updateInventoryItems(QStringList)));
    connect (e, SIGNAL(updateLocalItems(QStringList)), this, SLOT(updateLocalItems(QStringList)));

    // Use button group to make checkable item buttons exclusive.
    QButtonGroup *itemButtons = new QButtonGroup();
    itemButtons->addButton(ui->takeButton);
    itemButtons->addButton(ui->dropButton);
    itemButtons->addButton(ui->useButton);
    itemButtons->addButton(ui->examineButton);

    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(quit()));
    connect(ui->takeButton, SIGNAL(clicked()), this, SLOT(take()));
    connect(ui->dropButton, SIGNAL(clicked()), this, SLOT(drop()));
    connect(ui->useButton, SIGNAL(clicked()), this, SLOT(use()));
    connect(ui->examineButton, SIGNAL(clicked()), this, SLOT(examine()));

    connect(ui->lookButton, SIGNAL(clicked()), e, SLOT(doLook()));
    connect(ui->inventoryButton, SIGNAL(clicked()), e, SLOT(doInventory()));
    connect(ui->helpButton, SIGNAL(clicked()), e, SLOT(doHelp()));

    connect(ui->upButton, SIGNAL(clicked()), e, SLOT(doMoveUp()));
    connect(ui->downButton, SIGNAL(clicked()), e, SLOT(doMoveDown()));
    connect(ui->northButton, SIGNAL(clicked()), e, SLOT(doMoveNorth()));
    connect(ui->southButton, SIGNAL(clicked()), e, SLOT(doMoveSouth()));
    connect(ui->eastButton, SIGNAL(clicked()), e, SLOT(doMoveEast()));
    connect(ui->westButton, SIGNAL(clicked()), e, SLOT(doMoveWest()));

    // Put inventory buttons in a group.
    inventoryButtonGroup = new QButtonGroup();
    inventoryButtonGroup->addButton(ui->inventoryButton1, 0);
    inventoryButtonGroup->addButton(ui->inventoryButton2, 1);
    inventoryButtonGroup->addButton(ui->inventoryButton3, 2);
    inventoryButtonGroup->addButton(ui->inventoryButton4, 3);
    inventoryButtonGroup->addButton(ui->inventoryButton5, 4);

    // Put local object buttons in a group.
    objectButtonGroup = new QButtonGroup();
    objectButtonGroup->addButton(ui->objectButton1, 0);
    objectButtonGroup->addButton(ui->objectButton2, 1);
    objectButtonGroup->addButton(ui->objectButton3, 2);
    objectButtonGroup->addButton(ui->objectButton4, 3);
    objectButtonGroup->addButton(ui->objectButton5, 4);
    objectButtonGroup->addButton(ui->objectButton6, 5);

    // Start the game engine playing.
    e->start();
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

void MainWindow::take()
{
}

void MainWindow::drop()
{
}

void MainWindow::use()
{
}

void MainWindow::examine()
{
}

// This intercepts the window close so we can ask the user to confirm.
void MainWindow::closeEvent(QCloseEvent *event)
{
    quit();
    event->ignore(); // If we got here we do not want to quit.
}

// This updates the text when the game engine sends some output.
void MainWindow::updateWindow(QString s)
{
    ui->textEdit->append(s);
}

// This updates the label with number of turns.
void MainWindow::updateTurns(int turns)
{
    locationLabel->setText(tr("Turns: %1").arg(turns));
}

// This updates the label with current location.
void MainWindow::updateLocation(QString location)
{
    turnsLabel->setText(tr("Location: %1").arg(e->currentLocation()));
}

// This updates the UI when inventory items change.
void MainWindow::updateInventoryItems(QStringList items)
{
    int i = 0;
    foreach (QString item, items) {
        inventoryButtonGroup->button(i)->setText(item);
        i++;
    }
    for (; i < 5; ++i) {
        inventoryButtonGroup->button(i)->setText(tr("-"));
        inventoryButtonGroup->button(i)->setEnabled(false);
    }
}

// This updates the UI when local items change.
void MainWindow::updateLocalItems(QStringList items)
{
    int i = 0;
    foreach (QString item, items) {
        objectButtonGroup->button(i)->setText(item);
        i++;
    }
    for (; i < 6; ++i) {
        objectButtonGroup->button(i)->setText(tr("-"));
        objectButtonGroup->button(i)->setEnabled(false);
    }
}
