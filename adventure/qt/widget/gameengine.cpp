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

#include "gameengine.h"

// Constructor
GameEngine::GameEngine()
{
}

// Destructor
GameEngine::~GameEngine()
{
}

QStringList GameEngine::inventoryItems() const
{
    return QStringList();
}

int GameEngine::turnsPlayed() const
{
    return 99;
}

QString GameEngine::currentLocation() const
{
    return "driveway";
}

void GameEngine::doLook()
{
    qDebug("L@@k");
}

void GameEngine::doInventory()
{
}

void GameEngine:: doHelp()
{
}

void GameEngine::doQuit()
{
}

void GameEngine::doTake(QString item)
{
}

void GameEngine::doDrop(QString item)
{
}

void GameEngine::doUse(QString item)
{
}

void GameEngine::doExamine(QString item)
{
}

void GameEngine::doMoveUp()
{
}

void GameEngine::doMoveDown()
{
}

void GameEngine::doMoveNorth()
{
}

void GameEngine::doMoveSouth()
{
}

void GameEngine::doMoveEast()
{
}

void GameEngine::doMoveWest()
{
}

// emit sendOutput(QString output);
// emit updateInventoryItems(QStringList items);
// emit updateLocalItems(QStringList items);
// emit updateValidMoves(QStringList moves);
