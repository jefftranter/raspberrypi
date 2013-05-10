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

/* CONSTANTS */

/* Maximum number of items user can carry */
#define MAXITEMS 5

/* Number of locations */
#define NUMLOCATIONS 32

/* TYPES */

/* Directions */
typedef enum {
    North,
    South,
    East,
    West,
    Up,
    Down
} Direction_t;

/* Items */
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
    LastItem=OldRadio
} Item_t;

/* Locations */
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

/* TABLES */

/* Names of directions */
const char *DescriptionOfDirection[] = {
    "north", "south", "east", "west", "up", "down"
};

/* Names of items */
const char *DescriptionOfItem[LastItem+1] = {
    "",
    "key",
    "pitchfork",
    "flashlight",
    "lamp",
    "oil",
    "candybar",
    "bottle",
    "doll",
    "toy car",
    "matches",
    "gold coin",
    "silver coin",
    "stale meat",
    "book",
    "cheese",
    "old radio",
};

/* Names of locations */
const char *DescriptionOfLocation[NUMLOCATIONS] = {
    "",
    "in the driveway near your car",
    "in the driveway",
    "in front of the garage",
    "in front of the barn",
    "at the door to the house",
    "in the garage",
    "in the workroom of the barn",
    "in the hayloft of the barn",
    "in the kitchen",
    "in the dining room",
    "at the bottom of the stairs",
    "in the drawing room",
    "in the study",
    "at the top of the stairs",
    "in a boy's bedroom",
    "in a girl's bedroom",
    "in the master bedroom next to a bookcase",
    "in the servant's quarters",
    "in the basement laundry room",
    "in the furnace room",
    "in a vacant room next to a locked door",
    "in the cistern",
    "in an underground tunnel. there are rats here",
    "in the woods near a trapdoor",
    "in the woods",
    "in the woods",
    "in the woods next to a tree",
    "in the woods",
    "in the woods",
    "in the woods",
    "in the woods",
};

/* DATA */

/* Inventory of what player is carrying */
Item_t Inventory[MAXITEMS];

/* Location of each item. Index is the item number, returns the location. 0 if item is gone */
Location_t locationOfItem[LastItem+1];

/* Map. Given a location and a direction to move, returns the location it connects to, or 0 if not a valid move. Map can change during game play. */
int Move[NUMLOCATIONS][6] = {
    /* N  S  E  W  U  D */
    {  0, 0, 0, 0, 0, 0 }, /* 0 */
    {  2, 0, 0, 0, 0, 0 }, /* 1 */
    {  4, 1, 3, 5, 0, 0 }, /* 2 */
    {  0, 0, 6, 2, 0, 0 }, /* 3 */
    {  7, 2, 0, 0, 0, 0 }, /* 4 */
    {  0, 0, 2, 9, 0, 0 }, /* 5 */
    {  0, 0, 0, 3, 0, 0 }, /* 6 */
    {  0, 4, 0, 0, 8, 0 }, /* 7 */
    {  0, 0, 0, 0, 0, 7 }, /* 8 */
    {  0,10, 5, 0, 0,19 }, /* 9 */
    {  9, 0, 0,11, 0, 0 }, /* 10 */
    {  0, 0,10,12,14, 0 }, /* 11 */
    { 13, 0,11, 0, 0, 0 }, /* 12 */
    {  0,12, 0, 0, 0, 0 }, /* 13 */
    { 16, 0,15,17, 0,11 }, /* 14 */
    {  0, 0, 0,14, 0, 0 }, /* 15 */
    {  0,14, 0, 0, 0, 0 }, /* 16 */
    {  0, 0,14, 0, 0, 0 }, /* 17 */
    {  0, 0, 0, 0, 0,13 }, /* 18 */
    {  0, 0, 0,20, 9, 0 }, /* 19 */
    { 21, 0,19, 0, 0, 0 }, /* 20 */
    {  0,20, 0,22, 0, 0 }, /* 21 */
    {  0, 0,21, 0, 0, 0 }, /* 22 */
    { 24,21, 0, 0, 0, 0 }, /* 23 */
    { 29,23, 0,26, 0, 0 }, /* 24 */
    { 26, 0,24, 0, 0, 0 }, /* 25 */
    { 27,25,29, 0, 0, 0 }, /* 26 */
    {  0,26,28, 0, 0, 0 }, /* 27 */
    {  0,29,31,27, 0, 0 }, /* 28 */
    { 28,24,30,26, 0, 0 }, /* 29 */
    { 31, 0, 0,29, 0, 0 }, /* 30 */
    {  0,30, 0,29, 0, 0 }, /* 31 */
};

/* Return if carrying an item */
bool GameEngine::carryingItem(const char *item)
{
    for (int i = 0; i < MAXITEMS; i++) {
        if ((Inventory[i] != 0) && (!strcmp(DescriptionOfItem[Inventory[i]], item)))
            return 1;
    }
    return 0;
}

/* Return if item is at current location (but not carried) */
bool GameEngine::itemIsHere(const char *item)
{
    /* Find number of the item. */
    for (int i = 1; i <= LastItem; i++) {
        if (!strcmp(item, DescriptionOfItem[i])) {
            /* Found it, but is it here? */
            if (locationOfItem[i] == m_currentLocation) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    return 0;
}

/* Do special things unrelated to command being executed. */
void GameEngine::doSpecialActions()
{
    if ((m_turns == 10) && !m_lampLit) {
        printf("It will be getting dark soon. You need some kind of light or soon you won't be able to see.\n");
    }

    if ((m_turns >= 60) && (!m_lampLit || (!itemIsHere("lamp") && !carryingItem("lamp")))) {
        printf("It is dark out and you have no light. You stumble around for a while and then fall, hit your head, and pass out.\n");
        //bGameOver = 1;
        return;
    }

    if ((m_turns == 20) && !m_drankWater) {
        printf("You are getting very thirsty. You need to get a drink soon.\n");
    }

    if ((m_turns == 30) && !m_ateFood) {
        printf("You are getting very hungry. You need to find something to eat.\n");
    }

    if ((m_turns == 50) && !m_drankWater) {
        printf("You pass out due to thirst.\n");
        //bGameOver = 1;
        return;
    }

    if ((m_turns == 40) && !m_ateFood) {
        printf("You pass out from hunger.\n");
        //bGameOver = 1;
        return;
    }

    if (m_currentLocation == Tunnel) {
        if (itemIsHere("cheese")) {
            printf("The rats go after the cheese.\n");
        } else {
            if (m_ratAttack < 3) {
                printf("The rats are coming towards you!\n");
                ++m_ratAttack;
            } else {
                printf("The rats attack and you pass out.\n");
                //bGameOver = 1;
                return;
            }
        }
    }

    /* wolfState values:  0 - wolf attacking 1 - wolf gone, Matthew in tree. 2 - Matthew safe, you won. Game over. */
    if (m_currentLocation == WolfTree) {
        switch (m_wolfState) {
            case 0:
                printf("A wolf is circling around the tree. Matthew is up in the tree.\nYou have to save him! If only you had some kind of weapon!\n");
                break;
            case 1:
                printf("Matthew is afraid to come down from the tree.\nIf only you had something to coax him with.\n");
                break;
            case 2:
                printf("Congratulations! You succeeded and won the game.\nI hope you had as much fun playing the game as I did creating it.\n- Jeff Tranter <tranter@pobox.com>\n");
                //bGameOver = 1;
                return;
                break;
            }
    }
}

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

    msg = tr("\nYou are %1.\nYou see:").arg(DescriptionOfLocation[m_currentLocation]);

    bool seen = 0;
    for (int i = 1; i <= LastItem; i++) {
        if (locationOfItem[i] == m_currentLocation) {
            msg += tr("\n  %1").arg(DescriptionOfItem[i]);
            seen = 1;
        }
    }
    if (!seen) {
        msg += tr("  nothing special");
    }

    msg += tr("\nYou can go:");

    for (int i = North; i <= Down; i++) {
        int loc = Move[m_currentLocation][i];
        if (loc != 0) {
            msg += tr(" %1").arg(DescriptionOfDirection[i]);
        }
    }

    emit sendOutput(msg);
    doSpecialActions();
}

// Inventory command
void GameEngine::doInventory()
{
    bool found = false;
    QString msg;

    msg = tr("\nYou are carrying:");

    for (int i = 0; i < MAXITEMS; i++) {
        if (Inventory[i] != 0) {
            QString item = DescriptionOfItem[Inventory[i]];
            msg += tr("\n  %1").arg(item);
            found = 1;
        }
    }
    if (!found)
        msg += tr("\n  nothing");

    emit sendOutput(msg);
    doSpecialActions();
}

// Help command
void GameEngine:: doHelp()
{
    emit sendOutput(tr("\nHere are a few hints: I suggest drawing out a map on a piece of paper and making notes as you play the game. Pay attention to any messages, like needing food or water, as these will soon become important in the game. Not all items in the game are necessarily needed to solve it; some may be red herrings. The game will take some time to solve. Keep at it. If you get frustrated, set it aside for a while and you may think of some new insight into how to solve it."));
    doSpecialActions();
}

// Quit command
void GameEngine::doQuit()
{
}

// Take command.
void GameEngine::doTake(QString item)
{
    /* Find number of the item. */
    for (int i = 1; i <= LastItem; i++) {
        if (!strcmp(item.toLatin1(), DescriptionOfItem[i])) {
            /* Found it, but is it here? */
            if (locationOfItem[i] == m_currentLocation) {
            /* It is here. Add to inventory. */
            for (int j = 0; j < MAXITEMS; j++) {
                if (Inventory[j] == 0) {
                    Inventory[j] = (Item_t)i;
                    /* And remove from location. */
                    locationOfItem[i] = (Location_t)0;
                    emit sendOutput(tr("\nTook %1.").arg(item));

                    // Send notification that inventory changed
                    // TODO: Factor out into common code
                    m_inventoryItems.clear();
                    for (int i = 0; i < MAXITEMS; i++) {
                        if (Inventory[i] != 0) {
                            QString item = DescriptionOfItem[Inventory[i]];
                            m_inventoryItems << item;
                        }
                    }
                    emit updateInventoryItems(m_inventoryItems);

                    // Send notification that local items changed
                    // TODO: Factor out into common code

                    // Increment turns and notify
                    m_turns++;
                    emit updateTurns(m_turns);
                    return;
                }
            }

            /* Reached maximum number of items to carry */ 
            emit sendOutput(tr("\nYou can't carry any more. Drop something."));
            return;
            }
        }
    }

    /* If here, don't see it. */
    emit sendOutput(tr("\nI see no %1 here.").arg(item));

    doSpecialActions();
}

// Drop command.
void GameEngine::doDrop(QString item)
{
    Q_ASSERT(!item.isEmpty());

    // See if we have the item
    for (int i = 0; i < MAXITEMS; i++) {
        if ((Inventory[i] != 0) && (!strcmp(DescriptionOfItem[Inventory[i]], item.toLatin1()))) {
            // We have it. Add to location.
            locationOfItem[(Location_t)Inventory[i]] = (Location_t)m_currentLocation;
            // And remove from inventory
            Inventory[i] = (Item_t)0;
            emit sendOutput(tr("\nDropped %1.").arg(item));

            // Send notification that inventory changed
            // TODO: Factor out into common code
            m_inventoryItems.clear();
            for (int i = 0; i < MAXITEMS; i++) {
                if (Inventory[i] != 0) {
                    QString item = DescriptionOfItem[Inventory[i]];
                    m_inventoryItems << item;
                }
            }

            emit updateInventoryItems(m_inventoryItems);

            // Send notification that local items changed
            // TODO: Factor out into common code
            m_localItems <<item;
            emit updateLocalItems(m_localItems);

            // Increment turns and notify
            m_turns++;
            emit updateTurns(m_turns);

            return;
        }
    }

    // If here, don't have it.
    emit sendOutput(tr("\nNot carrying %1.").arg(item));
    doSpecialActions();
}

// Use command.
void GameEngine::doUse(QString item)
{
    emit sendOutput(tr("\nYou use the %1.").arg(item));

    char *sp;

    /* Command line should be like "U[SE] ITEM" Item name will be after after first space. */
    //sp = strchr(buffer, ' ');
    if (sp == NULL) {
        printf("Use what?\n");
        return;
    }

    item = sp + 1;

    /* Make sure item is being carried or is in the current location */
    if (!carryingItem(item.toLatin1()) && !itemIsHere(item.toLatin1())) {
        printf("I don't see it here.\n");
        return;
    }

////    m_turns++;

    /* Use key */
    if (!strcmp(item.toLatin1(), "key") && (m_currentLocation == VacantRoom)) {
        printf("You insert the key in the door and it opens, revealing a tunnel.\n");
        Move[21][North] = 23;
        return;
    }

    /* Use pitchfork */
    if (!strcmp(item.toLatin1(), "pitchfork") && (m_currentLocation == WolfTree) && (m_wolfState == 0)) {
        printf("You jab the wolf with the pitchfork. It howls and runs away.\n");
        m_wolfState = 1;
        return;
    }

    /* Use toy car */
    if (!strcmp(item.toLatin1(), "toy car") && (m_currentLocation == WolfTree && m_wolfState == 1)) {
        printf("You show matthew the toy car and he comes down to take it.\nYou take Matthew in your arms and carry him home.\n");
        m_wolfState = 2;
        return;
    }

    /* Use oil */
    if (!strcmp(item.toLatin1(), "oil")) {
        if (carryingItem("lamp")) {
            printf("You fill the lamp with oil.\n");
            m_lampFilled = 1;
            return;
        } else {
            printf("You don't have anything to use it with.\n");
            return;
        }
    }

    /* Use matches */
    if (!strcmp(item.toLatin1(), "matches")) {
        if (carryingItem("lamp")) {
            if (m_lampFilled) {
                printf("You light the lamp. You can see!\n");
                m_lampLit = 1;
                return;
            } else {
                printf("You can't light the lamp. It needs oil.\n");
                return;
            }
        } else {
            printf("Nothing here to light\n");
        }
    }
                
    /* Use candybar */
    if (!strcmp(item.toLatin1(), "candybar")) {
        printf("That hit the spot. You no longer feel hungry.\n");
        m_ateFood = 1;
        return;
    }

    /* Use bottle */
    if (!strcmp(item.toLatin1(), "bottle")) {
        if (m_currentLocation == Cistern) {
            printf("You fill the bottle with water from the cistern and take a drink.\nYou no longer feel thirsty.\n");
            m_drankWater = 1;
            return;
        } else {
            printf("The bottle is empty. If only you had some water to fill it!\n");
            return;
        }
    }

    /* Use stale meat */
    if (!strcmp(item.toLatin1(), "stale meat")) {
        printf("The meat looked and tasted bad. You feel very sick and pass out.\n");
        //bGameOver = 1;
        return;
    }

    /* Default */
    printf("Nothing happens\n");

    doSpecialActions();
}

// Examine command.
void GameEngine::doExamine(QString item)
{
    emit sendOutput(tr("\nYou examine the %1.").arg(item));

    char *sp;

    /* Command line should be like "E[XAMINE] ITEM" Item name will be after after first space. */
    //sp = strchr(buffer, ' ');
    if (sp == NULL) {
        printf("Examine what?\n");
        return;
    }

    item = sp + 1;
////    m_turns++;

    /* Examine bookcase - not an object */
    if (item == "bookcase") {
        printf("You pull back a book and the bookcase opens up to reveal a secret room.\n");
        Move[17][North] = 18;
        return;
    }

    /* Make sure item is being carried or is in the current location */
    if (!carryingItem(item.toLatin1()) && !itemIsHere(item.toLatin1())) {
        printf("I don't see it here.\n");
        return;
    }

    /* Examine Book */
    if (item == "book") {
        printf("It is a very old book entitled \"Apple 1 Operation Manual\".\n");
        return;
    }

    /* Examine Flashlight */
    if (item == "flashlight") {
        printf("It doesn't have any batteries.\n");
        return;
    }

    /* Examine toy car */
    if (item == "toy car") {
        printf("It is a nice toy car. Your grandson Matthew would like it.\n");
        return;
    }

    /* Examine old radio */
    if (item == "old radio") {
        printf("It is a 1940 Zenith 8-S-563 console with an 8A02 chassis. You'd turn it on but the electricity is off.\n");
        return;
    }

   /* Nothing special about this item */
   printf("You see nothing special about it.\n");

    doSpecialActions();
}

// Move command.
void GameEngine::doMoveUp()
{
    emit sendOutput(tr("\nYou cannot go up from here."));

    char *sp;
    char dirChar;
    Direction_t dir;

    /* Command line should be like "G[O] N[ORTH]" Direction will be
       the first letter after a space. Or just a single letter
       direction N S E W U D or full directon NORTH etc. */

    //sp = strrchr(buffer, ' ');
    if (sp != NULL) {
        dirChar = *(sp+1);
    } else {
        //dirChar = buffer[0];
    }

    if (dirChar == 'n') {
        dir = North;
    } else if (dirChar == 's') {
        dir = South;
    } else if (dirChar == 'e') {
        dir = East;
    } else if (dirChar == 'w') {
        dir = West;
    } else if (dirChar == 'u') {
        dir = Up;
    } else if (dirChar == 'd') {
        dir = Down;
    } else {
        printf("Go where?\n");
        return;
    }

    if (Move[m_currentLocation][dir] == 0) {
        printf("You can't go %s from here.\n", DescriptionOfDirection[dir]);
        return;
    }

    /* We can move */
    m_currentLocation = Move[m_currentLocation][dir];
    printf("You are %s.\n", DescriptionOfLocation[m_currentLocation]);
    m_turns++;

    doSpecialActions();
}

// Move command.
void GameEngine::doMoveDown()
{
    emit sendOutput(tr("\nYou move down."));
    m_location = tr("barn");
    emit updateLocation(m_location);
    m_turns++;
    emit updateTurns(m_turns);
    doSpecialActions();
}

// Move command.
void GameEngine::doMoveNorth()
{
    emit sendOutput(tr("\nYou move north."));
    m_location = tr("barn");
    emit updateLocation(m_location);
    m_turns++;
    emit updateTurns(m_turns);

    emit updateValidDirections(m_validDirections);

    if (m_turns > 10) {
        emit sendOutput(tr("\nYou took too many turns so you get... nothing!\nYou lose! Good day, sir!"));
        emit gameOver();
    }
    doSpecialActions();
}

// Move command.
void GameEngine::doMoveSouth()
{
    emit sendOutput(tr("\nYou move south."));
    doSpecialActions();
}

// Move command.
void GameEngine::doMoveEast()
{
    emit sendOutput(tr("\nYou move east."));
    doSpecialActions();
}

// Move command.
void GameEngine::doMoveWest()
{
    emit sendOutput(tr("\nYou move west."));
    doSpecialActions();
}

// Start (or restart) the game.
void GameEngine::start()
{

    /* Set variables to values for start of game */
    m_currentLocation = Driveway1;
    m_lampFilled = false;
    m_lampLit = false;
    m_ateFood = false;
    m_drankWater = false;
    m_ratAttack = 0;
    m_wolfState = 0;

    /* These doors can get changed during game and may need to be reset */
    Move[17][North] = 0;
    Move[21][North] = 0;

    /* Set inventory to default */
    memset(Inventory, 0, sizeof(Inventory[0])*MAXITEMS);
    Inventory[0] = Flashlight;

    /* Put items in their default locations */
    locationOfItem[0]  = (Location_t)0;    /* NoItem */
    locationOfItem[1]  = Driveway1;        /* Key */
    locationOfItem[2]  = Hayloft;          /* Pitchfork */
    locationOfItem[3]  = (Location_t)0;    /* Flashlight */
    locationOfItem[4]  = WorkRoom;         /* Lamp */
    locationOfItem[5]  = Garage;           /* Oil */
    locationOfItem[6]  = Kitchen;          /* Candybar */
    locationOfItem[7]  = Driveway2;        /* Bottle */
    locationOfItem[8]  = GirlsBedroom;     /* Doll */
    locationOfItem[9]  = BoysBedroom;      /* ToyCar */
    locationOfItem[10] = ServantsQuarters; /* Matches */
    locationOfItem[11] = Woods25;          /* GoldCoin */
    locationOfItem[12] = Woods29;          /* SilverCoin */
    locationOfItem[13] = DiningRoom;       /* StaleMeat */
    locationOfItem[14] = DrawingRoom;      /* Book */
    locationOfItem[15] = LaundryRoom;      /* Cheese */
    locationOfItem[16] = MasterBedroom;    /* OldRadio */

    m_turns = 0;

    m_location = tr("driveway");

    m_inventoryItems.clear();
    for (int i = 0; i < MAXITEMS; i++) {
        if (Inventory[i] != 0) {
            QString item = DescriptionOfItem[Inventory[i]];
            m_inventoryItems << item;
        }
    }

    m_localItems.clear();

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
