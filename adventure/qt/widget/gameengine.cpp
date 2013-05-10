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

    msg += tr("\nYou can go: up north south");
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
void GameEngine:: doHelp()
{
    emit sendOutput(tr("Here are a few hints: I suggest drawing out a map on a piece of paper and making notes as you play the game. Pay attention to any messages, like needing food or water, as these will soon become important in the game. Not all items in the game are necessarily needed to solve it; some may be red herrings. The game will take some time to solve. Keep at it. If you get frustrated, set it aside for a while and you may think of some new insight into how to solve it."));
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
    emit sendOutput(tr("You cannot go up from here."));
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
    emit sendOutput(tr("You move north."));
    m_location = tr("barn");
    emit updateLocation(m_location);
    m_turns++;
    emit updateTurns(m_turns);

    emit updateValidDirections(m_validDirections);

    if (m_turns > 10) {
        emit sendOutput(tr("You took too many turns so you get... nothing!\nYou lose! Good day, sir!"));
        emit gameOver();
    }
}

// Move command.
void GameEngine::doMoveSouth()
{
    emit sendOutput(tr("You move south."));
}

// Move command.
void GameEngine::doMoveEast()
{
    emit sendOutput(tr("You move east."));
}

// Move command.
void GameEngine::doMoveWest()
{
    emit sendOutput(tr("You move west."));
}

// Start (or restart) the game.
void GameEngine::start()
{
    m_turns = 0;
    m_location = tr("driveway");
    m_inventoryItems.clear();
    m_inventoryItems << tr("flashlight") << tr("doll") << tr("pitchfork") << tr("lamp");
    m_localItems.clear();
    m_localItems << tr("key") << tr("toy car") << tr("matches");
    m_validDirections.clear();
    m_validDirections << tr("up") << tr("north") << tr("south");

    emit updateTurns(m_turns);
    emit updateLocation(m_location);
    emit updateInventoryItems(m_inventoryItems);
    emit updateLocalItems(m_localItems);
    emit updateValidDirections(m_validDirections);

    emit sendOutput(tr(
"                    The Abandoned Farmhouse Adventure\n"
"                    By Jeff Tranter <tranter@pobox.com>\n"
"\n"
"Your four-year-old grandson has gone missing and was last seen headed in the direction of the abandoned family farm. It's a dangerous place to play. You have to find him before he gets hurt, and it will be getting dark soon..."
                       ));

}
