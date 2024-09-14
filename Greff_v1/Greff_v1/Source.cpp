#include <iostream>
#include <vector>
#include "gamestate.h";
 
using namespace std;
//void memory_dump(gamestate game);
void configure(gamestate& game);

int main(){
	gamestate game = game;
	configure(game);
	system("CLS");

	game.Crntchapter.dump_chapter();
	game.dump_art();
	game.draw_art("cover");
	game.brake();
	system("CLS");

	while (true)
	{
		game.play_game();
	}
	return 0;
}

void configure(gamestate& game) {
	

	string line;
	ifstream myfile("configure.txt");
	bool mode = true;
	while (getline(myfile, line))
	{
		if (mode) {
			if (line[0] != '#')
			{
				game.Chapters.push_back(chapter(line));
			}
			else
			{
				mode = false;
			}
		}
		else {
			if (line[0] != '#')
			{
				game.read_art(line);
			}
			else
			{
				break;
			}
		}

		game.Crntchapter = game.Chapters[0];
		game.position = game.Crntchapter.rooms[0];
		
		
	}
}
