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

// CONSTANTS

// Maximum number of items user can carry
static const int maxItems = 5;

// Number of locations
static const int numLocations = 32;

// TYPES

/* Directions */
typedef enum {
    North,
    South,
    East,
    West,
    Up,
    Down
} Direction_t;

// Items
typedef enum {
    NoItem,
    Key,
    Pitchfork,
    Flashlight,
    Lamp,
    Oil,
    Candybar,
    Bottle,
    Doll,
    ToyCar,
    Matches,
    GoldCoin,
    SilverCoin,
    StaleMeat,
    Book,
    Cheese,
    OldRadio,
    BookCase,
    LastItem=BookCase
} Item_t;

// Locations
typedef enum {
    NoLocation,
    Driveway1,
    Driveway2,
    Driveway3,
    Driveway4,
    Driveway5,
    Garage,
    WorkRoom,
    Hayloft,
    Kitchen,
    DiningRoom,
    BottomStairs,
    DrawingRoom,
    Study,
    TopStairs,
    BoysBedroom,
    GirlsBedroom,
    MasterBedroom,
    ServantsQuarters,
    LaundryRoom,
    FurnaceRoom,
    VacantRoom,
    Cistern,
    Tunnel,
    Woods24,
    Woods25,
    Woods26,
    WolfTree,
    Woods28,
    Woods29,
    Woods30,
    Woods31,
} Location_t;

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
    bool itemIsHere(const QString item);
    bool carryingItem(const QString item);

public slots:
    // Global commands
    void doLook();
    void doInventory();
    void doHelp();
    void doQuit();

    // Item commands
    void doTake(const QString item);
    void doDrop(const QString item);
    void doUse(const QString item);
    void doExamine(const QString item);

    // Move commands
    void doMoveUp();
    void doMoveDown();
    void doMoveNorth();
    void doMoveSouth();
    void doMoveEast();
    void doMoveWest();

signals:
    void sendOutput(const QString output);
    void updateLocation(const QString location);
    void updateTurns(int turns);
    void updateInventoryItems(const QStringList items);
    void updateLocalItems(const QStringList items);
    void updateValidDirections(const QStringList moves);
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
