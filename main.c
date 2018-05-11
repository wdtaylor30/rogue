#if 0
William Daniel Taylor
5.7.18
The beginnings of a roguelike RPG...
Resume at Part VI 4:37
#endif

/* When compiling, use -lncurses and -std=c99 flags */

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

//position
typedef struct Position
{
	int x;
	int y;
}Position;

//player building
typedef struct Player
{
	Position position;
	int hp;
}Player;

//room building
typedef struct Room
{
	Position position;	
	int height;
	int width;
	
	//doors
	Position door[4];
}Room;

//environment building
void screenSetup();
Room** mapSetup();
Room* createRoom(int y, int x, int height, int width);
void drawRoom(Room* room);
Player* playerSetup();

//user input and movement
void handleInput(int input, Player* user);
void playerMove(int y, int x, Player* user);
void checkPosition(int newY, int newX, Player* user);

/*Main */
int main()
{
	//initialize environment
	screenSetup();
	mapSetup();

	//create player
	Player* user;
	user = playerSetup();

	//main game loop
	int ch;
	while ((ch = getch()) != 'q')
	{
		handleInput(ch, user);
	}//end while

	endwin();

	return 0;
}//end main


void screenSetup()
{
	initscr();
	printw("Press 'q' to exit.");
	noecho();
	refresh();

	return;
}//end method

Room** mapSetup()
{
	Room** rooms;
	rooms = malloc(sizeof(Room) * 6);

	/* ROOM ONE */
	//generate room information
	rooms[0] = createRoom(13, 13, 6, 8);

	//draw room
	drawRoom(rooms[0]);


	/* ROOM TWO */
	//generate room information
	rooms[1] = createRoom(2, 40, 6, 8);
	
	//draw room
	drawRoom(rooms[1]);


	/* ROOM THREE */
	//generate room information
	rooms[2] = createRoom(10, 40, 6, 8);

	//draw room
	drawRoom(rooms[2]);

	
	return rooms;
}//end method

Room* createRoom (int y, int x, int height, int width)
{
	Room* newRoom;
	newRoom = malloc(sizeof(Room));

	//assign values
	newRoom->position.x = x;
	newRoom->position.y = y;
	newRoom->height = height;
	newRoom->width = width;
	
	/* Top door */
	srand(time(NULL));
	newRoom->door[0].y = newRoom->position.y;
	newRoom->door[0].x = rand() % width;
	
	/* Bottom door */
	srand(time(NULL));
	newRoom->door[0].y = newRoom->position.y;
	newRoom->door[0].x = rand() % width;
	
	return newRoom;	
}//end method

void drawRoom(Room* room)
{
	int x, y;

	//draw top and botom walls
	for (x = room->position.x; x < room->position.x + room->width; x++)
	{
		//top
		mvprintw(room->position.y, x, "-");
		//bottom
		mvprintw(room->position.y + room->height - 1, x, "-");
	}//end for

	//draw walkways
	for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++)
	{
		//side walls
		mvprintw(y, room->position.x, "|");
		mvprintw(y, room->position.x + room->width - 1, "|");

		for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++)
		{
			//floors
			mvprintw(y, x, ".");
		}//end nested for
	}//end for
}//end method

Player* playerSetup()
{
	Player* newPlayer;
	newPlayer = malloc(sizeof(Player));

	//starting position
	newPlayer->position.x = 14;
	newPlayer->position.y = 14;

	//health
	newPlayer->hp = 100;

	//draw player and move cursor back
	playerMove(14, 14, newPlayer);


	return newPlayer;
}//end method

void handleInput(int input, Player* user)
{
	int newY, newX;
	switch(input)
	{
		//move up
		case 'w':
		case 'W':
			newY = user->position.y - 1;
			newX = user->position.x;
			break;

		//move down
		case 's':
		case 'S':
			newY = user->position.y + 1;
			newX = user->position.x;
			break;

		//move left
		case 'a':
		case 'A':
			newY = user->position.y;
			newX = user->position.x - 1;
			break;

		//move right
		case 'd':
		case 'D':
			newY = user->position.y;
			newX = user->position.x + 1;
			break;

		//default
		default:
			break;
	}//end switch

	//check for obstructions (collision detection)
	checkPosition(newY, newX, user);
}//end method

/* Collision Detection */
void checkPosition(int newY, int newX, Player* user)
{
	//int space;
	switch (mvinch(newY, newX))
	{
		//mvinch() finds floor; allow movement
		case '.':
			playerMove(newY, newX, user);
			break;

		//otherwise, do not allow movement
		default:
			move(user->position.y, user->position.x);
			break;
	}//end switch
}//end method

void playerMove(int y, int x, Player* user)
{
	//replace player with floor
	mvprintw(user->position.y, user->position.x, ".");

	//update user positon
	user->position.y = y;
	user->position.x = x;

	//draw player and move cursor back
	mvprintw(user->position.y, user->position.x, "@");
	move(user->position.y, user->position.x);
}//end method
