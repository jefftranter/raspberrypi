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
    void about();
    void gameOver();
    void commandOnItem(QAbstractButton *button);
    void updateWindow(QString msg);
    void updateTurns(int turns);
    void updateLocation(QString location);
    void updateInventoryItems(QStringList items);
    void updateLocalItems(QStringList items);
    void updateValidDirections(QStringList moves);
    void save();
    void saveAs();
    void open();

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
    QString m_fileName;
};

#endif // MAINWINDOW_H
