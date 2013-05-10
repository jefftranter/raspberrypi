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

/* Directions */
typedef enum {
    North,
    South,
    East,
    West,
    Up,
    Down
} Direction_t;

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
    bool itemIsHere(const char *item);
    bool carryingItem(const char *item);

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
    void updateLocation(QString location);
    void updateTurns(int turns);
    void updateInventoryItems(QStringList items);
    void updateLocalItems(QStringList items);
    void updateValidDirections(QStringList moves);
    void gameOver();

 private:
    // Private methods
    void doSpecialActions();
    void recalculateLocalVariables();
    void doMove(Direction_t dir);

private:
    int m_turns;              // Number of turns played
    int m_currentLocation;    // Current location
    bool m_lampLit;           // True if player has lit the lamp
    bool m_lampFilled;        // True if lamp filled with oil
    bool m_ateFood;           // True if player ate food
    bool m_drankWater;        // True if player drank water
    int m_ratAttack;          // Incremented each turn you are in the tunnel
    int m_wolfState;          // Tracks state of wolf attack
    QString m_location;
    QStringList m_inventoryItems;
    QStringList m_localItems;
    QStringList m_validDirections;
};
#endif /* GAMEENGINE_H */
