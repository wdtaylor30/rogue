#if 0
William Daniel Taylor
5.7.18
The beginnings of a roguelike RPG...
#endif

/* When compiling, use -lncurses and -std=c99 flags */

#include <ncurses.h>
#include <stdlib.h>

//player building
typedef struct Player
{
	int xPos;
	int yPos;
	int hp;
}Player;

//environment building
void screenSetup();
void mapSetup();
Player * playerSetup();

//user input and movement
void handleInput(int input, Player * user);
void playerMove(int y, int x, Player * user);

/*Main */
int main()
{
	//initialize environment
	screenSetup();
	mapSetup();

	//create player
	Player * user;
	user = playerSetup();

	//main game loop
	int ch;
	while ((ch = getch()) != 'q')
	{
		handleInput(ch, user);
	}
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

void mapSetup()
{
	//mvprintw(y, x, "string")

	//top wall
	mvprintw(13, 13, "--------");

	//walkways
	for (int y = 14; y <= 17; y++)
	{
		mvprintw(y, 13, "|......|");
	}//end for

	//bottom wall
	mvprintw(18, 13, "--------");
}//end method

Player * playerSetup()
{
	Player * newPlayer;
	newPlayer = malloc(sizeof(Player));

	//starting position
	newPlayer->xPos = 14;
	newPlayer->yPos = 14;

	//health
	newPlayer->hp = 100;

	//draw player and move cursor back
	playerMove(14, 14, newPlayer);


	return newPlayer;
}//end method

void handleInput(int input, Player * user)
{
	switch(input)
	{
		//move up
		case 'w':
		case 'W':
			playerMove(user->yPos - 1, user->xPos, user);
			break;

		//move down
		case 's':
		case 'S':
			playerMove(user->yPos + 1, user->xPos, user);
			break;

		//move left
		case 'a':
		case 'A':
			playerMove(user->yPos, user->xPos - 1, user);
			break;

		//move right
		case 'd':
		case 'D':
			playerMove(user->yPos, user->xPos + 1, user);
			break;

		//default
		default:
			break;
	}//end switch
}//end method

void playerMove(int y, int x, Player * user)
{
	//replace player with floor
	mvprintw(user->yPos, user->xPos, ".");

	//update user positon
	user->yPos = y;
	user->xPos = x;

	//draw player and move cursor back
	mvprintw(user->yPos, user->xPos, "@");
	move(user->yPos, user->xPos);
}//end method
