# Ships

## Description

The aim of the project is to write a simple game Battleship.
Then extend it, so it will become interesting.
Consult https://en.wikipedia.org/wiki/Battleship_(game) for an overview.
The rules are modified a bit so the progress made on basic version is not lost when the game is extended.

---

## Tasks

1. The board can be of arbitrary size.
1. There are 2 players: A and B. First starts player A by default.
1. 1 ship of size 5 **[CAR]**, 2 ships of size 4 **[BAT]**, 3 ships of size 3 **[CRU]**, 4 ships of size 2 **[DES]**
1. Player can insert ships on the board.
1. Player can make an order to move a ship.
1. Players can make moves, one after another, the only possible move is to either place the ships,
shot one shot at a given position ( number of shoots equal to the size of the ship )
or move the ship (CAR up to 2 times, other up to 3 times).
1. Game can detect which players wins.
1. The game can print the state of the game.
1. Printing from player's perspective also, the numbers of rows and columns should be printed.
1. Reefs, i.e. forbidden fields on the map and no ship under any circumstances can be present on such a field.
1. Each of the ships contain 2 sections: cannon as a field after head, and engine at it is back.
1. The size of ship determines the range of the cannon. For carrier it is infinite, for others _ship_size = sqrt(|y1-y2|^2 + |x1-x2|^2)_
1. If the engine is damaged the ship cannot move. If the cannon is damaged the ship cannot shoot.
1. Ships contains additional section, radar at it's head. Radar provides an information about positions of other ships.
If the radar is damaged, then the range of the radar is 1. Otherwise it is the length of the ship. The field uses the same formula as for the cannon.
1. CAR can send spy planes (number of shoots - 5), the planes revel presence of enemy ships in 3x3 square each.
1. Printing (Saving) the state of the game.

---

## Commands 

The basic logic is in bold

### [state]

1. **`PRINT x` - For x = 0 it is the basic version:**
	- ‘+’ means that the field is occupied by a ship.
	- 'x' means that there is a destroyed fragment at the position.
	- ' ' means that the position is empty.
	For x = 1 it is the advanced version:
	- '#' means there is a reef.
	- '%' as engine.
	- '!' as cannon.
	- '@' as radar.
1. **`SET_FLEET P a1 a2 a3 a4` - The number of ships of consecutive classes for the player P.**
1. **`NEXT_PLAYER P` - Sets an information that P should make move next.**
1. `BOARD_SIZE y x` - Set the board size to y times x.
1. `INIT_POSITION P y1 x1 y2 x2` - Player can place ships in [y1, y2] in Y dimension and in [x1, x2] in X dimension.
1. `REEF y x` - There is a reef at position (y,x).
1. `SHIP P y x D i C a1...al` - P position (y,x), D direction(N/W/S/E), C class(CAR/BAT/CRU/DES), state of the segments are a1 … al (1 means that the part is not destroyed, 0 that it was destroyed).
1. `EXTENDED_SHIPS` - Turn the extended logic of ships.
1. `SRAND x` - Seed of chosen random number generator to x.
1. `SAVE` - Save the commands that allows to recreate the state of the game.

### [playerX]

1. **`PLACE_SHIP y x D i C` - Place the i-th ship of class C at (y,x) with direction equal to D(N/W/S/E).**
1. **`SHOOT y x` - Shoot at the field (y,x).**
1. `MOVE i C x` - Move the i-th ship of class C x ([F]orward, [L]eft, [R]ight)
1. `SHOOT i C y x` - Let one of the shoots of i-th class ship be at (y,x).
1. `SPY i y x` - Send a spy plane from i-th carrier at the position (y,x).
1. `PRINT x` - For x = 0 use basic printing. For x = 1 advanced one.

---

## Validation

The basic logic is in bold

1. **`PLACE_SHIP`**
	- **_NOT IN STARTING POSITION_** - the ships are not in starting positions of players.
	- **_SHIP ALREADY PRESENT_** - the same ship is not added twice.
	- **_ALL SHIPS OF THE CLASS ALREADY SET_** - that it is not adding too many ships to a given class.
1. **`SHOOT`**
	- **_FIELD DOES NOT EXIST_** - the shoot isn't at a position in the board.
	- **_NOT ALL SHIPS PLACED_** - and that all ships that should be placed were already placed.
1. **_THE OTHER PLAYER EXPECTED_** - used a command for a different player than expected.
1. `SHIP`
	- _PLACING SHIP ON REEF_ - the ship must be not placed on reefs.
	- _PLACING SHIP TOO CLOSE TO OTHER SHIP_ - the ship is placed too close to other ship.
	- _SHIP ALREADY PRESENT_ - the same ship is not added twice.
	- _ALL SHIPS OF THE CLASS ALREADY SET_ - that it is not adding too many ships to a given class.
1. _REEF IS NOT PLACED ON BOARD_ - REEF should verify that is placed on board.
1. `PLACE_SHIP`
	- _PLACING SHIP ON REEF_ - the ship must be not placed on reefs.
	- _PLACING SHIP TOO CLOSE TO OTHER SHIP_ - the ship is placed at least on tile away from other ship.
1. `SHOOT`
	- _SHIP CANNOT SHOOT_ - the ship has destroyed cannon.
	- _TOO MANY SHOOTS_ - the ship took too many shots.
	- _SHOOTING TOO FAR_ - ship didn't fire within range of the guns.
1. `MOVE`
	- _SHIP CANNOT MOVE_ - the ship has destroyed engine.
	- _SHIP MOVED ALREADY_ - the ship is not moving too many times.
	- _PLACING SHIP ON REEF_ - the ship is placed on reef.
	- _SHIP WENT FROM BOARD_ - the ship moves out of board.
	- _PLACING SHIP TOO CLOSE TO OTHER SHIP_ - the ship is placed too close to other ships.
1. `SPY`
	- _CANNOT SEND PLANE_ - the ship has destroyed cannon.
	- _ALL PLANES SENT_ - the ship is sending too many planes.