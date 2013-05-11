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

#include <QButtonGroup>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameengine.h"

const int numInventoryButtons = 5; // Number of inventory buttons in UI
const int numLocalItemButtons = 6; // Number of local item buttons in UI

// Constructor.
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initialize();
}

// Destructor.
MainWindow::~MainWindow()
{
    delete m_game;
    delete ui;
}

// Do iniitalization
void MainWindow::initialize()
{
    // Create game engine
    m_game = new GameEngine;

    // Create labels in status bar
    m_turnsLabel = new QLabel();
    m_directionsLabel = new QLabel();
    m_locationLabel = new QLabel();
    statusBar()->addWidget(m_turnsLabel, 1);
    statusBar()->addWidget(m_directionsLabel, 1);
    statusBar()->addWidget(m_locationLabel, 1);

    // Put inventory buttons in a group.
    m_inventoryButtonGroup = new QButtonGroup();
    m_inventoryButtonGroup->addButton(ui->inventoryButton1, 0);
    m_inventoryButtonGroup->addButton(ui->inventoryButton2, 1);
    m_inventoryButtonGroup->addButton(ui->inventoryButton3, 2);
    m_inventoryButtonGroup->addButton(ui->inventoryButton4, 3);
    m_inventoryButtonGroup->addButton(ui->inventoryButton5, 4);

    // Put local object buttons in a group.
    m_objectButtonGroup = new QButtonGroup();
    m_objectButtonGroup->addButton(ui->objectButton1, 0);
    m_objectButtonGroup->addButton(ui->objectButton2, 1);
    m_objectButtonGroup->addButton(ui->objectButton3, 2);
    m_objectButtonGroup->addButton(ui->objectButton4, 3);
    m_objectButtonGroup->addButton(ui->objectButton5, 4);
    m_objectButtonGroup->addButton(ui->objectButton6, 5);

    // Use button group to make checkable item buttons exclusive.
    QButtonGroup *itemButtons = new QButtonGroup();
    itemButtons->addButton(ui->takeButton);
    itemButtons->addButton(ui->dropButton);
    itemButtons->addButton(ui->useButton);
    itemButtons->addButton(ui->examineButton);

    // Signal/slot connections
    connect(m_game, SIGNAL(sendOutput(QString)), this, SLOT(updateWindow(QString)));
    connect(m_game, SIGNAL(updateLocation(QString)), this, SLOT(updateLocation(QString)));
    connect(m_game, SIGNAL(updateTurns(int)), this, SLOT(updateTurns(int)));
    connect(m_game, SIGNAL(updateInventoryItems(QStringList)), this, SLOT(updateInventoryItems(QStringList)));
    connect(m_game, SIGNAL(updateLocalItems(QStringList)), this, SLOT(updateLocalItems(QStringList)));
    connect(m_game, SIGNAL(updateValidDirections(QStringList)), this, SLOT(updateValidDirections(QStringList)));
    connect(m_game, SIGNAL(gameOver()), this, SLOT(gameOver()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(quit()));
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(quit()));
    connect(ui->lookButton, SIGNAL(clicked()), m_game, SLOT(doLook()));
    connect(ui->inventoryButton, SIGNAL(clicked()), m_game, SLOT(doInventory()));
    connect(ui->helpButton, SIGNAL(clicked()), m_game, SLOT(doHelp()));
    connect(ui->upButton, SIGNAL(clicked()), m_game, SLOT(doMoveUp()));
    connect(ui->downButton, SIGNAL(clicked()), m_game, SLOT(doMoveDown()));
    connect(ui->northButton, SIGNAL(clicked()), m_game, SLOT(doMoveNorth()));
    connect(ui->southButton, SIGNAL(clicked()), m_game, SLOT(doMoveSouth()));
    connect(ui->eastButton, SIGNAL(clicked()), m_game, SLOT(doMoveEast()));
    connect(ui->westButton, SIGNAL(clicked()), m_game, SLOT(doMoveWest()));
    connect(m_inventoryButtonGroup, SIGNAL(buttonClicked(QAbstractButton *)), this, SLOT(commandOnItem(QAbstractButton *)));
    connect(m_objectButtonGroup, SIGNAL(buttonClicked(QAbstractButton *)), this, SLOT(commandOnItem(QAbstractButton *)));

    // Initially check one item command button.
    ui->takeButton->setChecked(true);

    // Start the game engine playing.
    m_game->start();
}

// Handle quit.
void MainWindow::quit()
{
    int button = QMessageBox::question(this, tr("Confirm Quit"), tr("Are you sure you want to quit?"), QMessageBox::Yes|QMessageBox::No);
    if (button == QMessageBox::Yes) {
        qApp->quit();
    }
}

// Handle game ending.
void MainWindow::gameOver()
{
    int turns = m_game->turnsPlayed();
    int button = QMessageBox::question(this, tr("Game Over"), tr("Game over after %1 turns.\nDo you want to play again?").arg(turns), QMessageBox::Yes|QMessageBox::No);
    if (button == QMessageBox::No) {
        qApp->quit();
    } else {
        ui->textEdit->clear();
        m_game->start();
    }
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
    m_turnsLabel->setText(tr("<b>Turns:</b> %1").arg(turns));
}

// This updates the label with current location.
void MainWindow::updateLocation(QString location)
{
    m_locationLabel->setText(tr("<b>Location:</b> %1").arg(location));
}

// This updates the label with valid directions and enabled the appropriate move buttons.
void MainWindow::updateValidDirections(QStringList moves)
{
    m_directionsLabel->setText(tr("<b>Can move:</b> %1").arg(moves.join(tr(", "))));

    // Enable the appropriate move buttons
    ui->upButton->setEnabled(moves.contains(tr("up")));
    ui->downButton->setEnabled(moves.contains(tr("down")));
    ui->northButton->setEnabled(moves.contains(tr("north")));
    ui->southButton->setEnabled(moves.contains(tr("south")));
    ui->eastButton->setEnabled(moves.contains(tr("east")));
    ui->westButton->setEnabled(moves.contains(tr("west")));
}

// This updates the UI when inventory items change.
void MainWindow::updateInventoryItems(QStringList items)
{
    int i = 0;
    foreach (QString item, items) {
        m_inventoryButtonGroup->button(i)->setText(item);
        m_inventoryButtonGroup->button(i)->setEnabled(true);
        i++;
        // Should not be possible to have more items than buttons but handle it just in case.
        if (i == numInventoryButtons) {
            return;
        }
    }

    // Set remaining buttons to blank and disable them.
    for (; i < numInventoryButtons; ++i) {
        m_inventoryButtonGroup->button(i)->setText(tr("-"));
        m_inventoryButtonGroup->button(i)->setEnabled(false);
    }
}

// This updates the UI when local items change.
void MainWindow::updateLocalItems(QStringList items)
{
    int i = 0;
    foreach (QString item, items) {
        m_objectButtonGroup->button(i)->setText(item);
        m_objectButtonGroup->button(i)->setEnabled(true);
        i++;
        // It is possible to have more items than buttons.
        if (i == numLocalItemButtons) {
            return;
        }
    }

    // Set remaining buttons to blank and disable them.
    for (; i < numLocalItemButtons; ++i) {
        m_objectButtonGroup->button(i)->setText(tr("-"));
        m_objectButtonGroup->button(i)->setEnabled(false);
    }
}

// Handle pressing button to perform a command on an item.
void MainWindow::commandOnItem(QAbstractButton *button)
{
    QString item = button->text();
    Q_ASSERT(!item.isEmpty());
    Q_ASSERT(item != tr("-"));

    if (ui->takeButton->isChecked()) {
        m_game->doTake(item);
    } else if (ui->dropButton->isChecked()) {
        m_game->doDrop(item);
    } else if (ui->useButton->isChecked()) {
        m_game->doUse(item);
    } else if (ui->examineButton->isChecked()) {
        m_game->doExamine(item);
    } else {
        Q_ASSERT(false);
    }
}
