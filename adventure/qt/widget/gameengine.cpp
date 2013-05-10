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
#include "gameengine.h"

// Constructor
GameEngine::GameEngine()
{
}

// Destructor
GameEngine::~GameEngine()
{
}

// Return current inventory items.
QStringList GameEngine::inventoryItems() const
{
    return m_inventoryItems;
}

// Return local items.
QStringList GameEngine::localItems() const
{
    return m_localItems;
}

// Return number of turns played.
int GameEngine::turnsPlayed() const
{
    return m_turns;
}

// Return current location (a short string).
QString GameEngine::currentLocation() const
{
    return m_location;
}

// Look command
void GameEngine::doLook()
{
    QString msg;

    msg = tr("You are in the driveway near your car.\nYou see:");

    foreach (QString item, m_localItems) {
        msg += tr("\n  ") + item;
    }

    msg += tr("\nYou can go: up north south\n");
    emit sendOutput(msg);
}

// Inventory command
void GameEngine::doInventory()
{
    QString msg;
    msg = tr("You are carrying:");
    foreach (QString item, m_inventoryItems) {
        msg += tr("\n  ") + item;
    }
    emit sendOutput(msg);
}

// Help command
// TODO: Output more appropriate help text for GUI version.
void GameEngine:: doHelp()
{
    emit sendOutput(
    "Valid commands:\n"
    "go east/west/north/south/up/down\n"
    "look\n"
    "use <object>\n"
    "examine <object>\n"
    "take <object>\n"
    "drop <object>\n"
    "inventory\n"
    "help\n"
    "quit\n"
    "You can abbreviate commands and directions to the first letter.\n"
    "Type just the first letter of a direction to move.\n");

}

// Quit command
void GameEngine::doQuit()
{
}

// Take command.
void GameEngine::doTake(QString item)
{
    emit sendOutput("You take the " + item + ".");
}

// Drop command.
void GameEngine::doDrop(QString item)
{
    emit sendOutput("You drop the " + item + ".");
}

// USe command.
void GameEngine::doUse(QString item)
{
    emit sendOutput("You use the " + item + ".");
}

// Examine command.
void GameEngine::doExamine(QString item)
{
    emit sendOutput("You examine the " + item + ".");
}

// Move command.
void GameEngine::doMoveUp()
{
    emit sendOutput(tr("You cannot go up from here.\n"));
}

// Move command.
void GameEngine::doMoveDown()
{
    emit sendOutput("You move down.");
    m_location = tr("barn");
    emit updateLocation(m_location);
    m_turns++;
    emit updateTurns(m_turns);
}

// Move command.
void GameEngine::doMoveNorth()
{
    emit sendOutput("You move north.");
    m_location = tr("barn");
    emit updateLocation(m_location);
    m_turns++;
    emit updateTurns(m_turns);

    emit updateValidDirections(m_validDirections);

    if (m_turns > 10) {
        emit sendOutput("You took too many turns so you get... nothing!\nYou lose! Good day, sir!");
        emit gameOver();
    }
}

// Move command.
void GameEngine::doMoveSouth()
{
    emit sendOutput("You move south.");
}

// Move command.
void GameEngine::doMoveEast()
{
    emit sendOutput("You move east.");
}

// Move command.
void GameEngine::doMoveWest()
{
    emit sendOutput("You move west.");
}

// Start (or restart) the game.
void GameEngine::start()
{
    m_turns = 0;
    m_location = tr("driveway");
    m_inventoryItems << tr("flashlight") << "doll" << "pitchfork" << "lamp";
    m_localItems << tr("key") << "toy car" << "matches";
    m_validDirections << tr("up") << tr("north") << tr("south");

    emit updateTurns(m_turns);
    emit updateLocation(m_location);
    emit updateInventoryItems(m_inventoryItems);
    emit updateLocalItems(m_localItems);
    emit updateValidDirections(m_validDirections);

    emit sendOutput(
"                        Abandoned Farmhouse Adventure\n"
"                                By Jeff Tranter\n"
"\n"
"Your four year old grandson has gone missing and was last seen headed in the\n"
"direction of the abandoned family farm. It's a dangerous place to play.\n"
"You have to find him before he gets hurt, and it will be getting dark soon...\n"
);

}
