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

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <QObject>
#include <QString>
#include <QStringList>

class GameEngine : public QObject
{
    Q_OBJECT;

public:
    // Constructor
    GameEngine();

    // Destructor
    ~GameEngine();

    // Accessors
    QStringList inventoryItems() const;
    QStringList localItems() const;
    int turnsPlayed() const;
    QString currentLocation() const;

    // Methods
    void start();

public slots:
    // Global commands
    void doLook();
    void doInventory();
    void doHelp();
    void doQuit();

    // Item commands
    void doTake(QString item);
    void doDrop(QString item);
    void doUse(QString item);
    void doExamine(QString item);

    // Move commands
    void doMoveUp();
    void doMoveDown();
    void doMoveNorth();
    void doMoveSouth();
    void doMoveEast();
    void doMoveWest();

 signals:
    void sendOutput(QString output);
    void locationChanged();
    void updateInventoryItems(QStringList items);
    void updateLocalItems(QStringList items);
    void updateValidMoves(QStringList moves);

 private:
    int m_turns;
    QString m_location;
    QStringList m_inventoryItems;
    QStringList m_localItems;
};
#endif /* GAMEENGINE_H */
