#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>

#include "art.h"
#include "object.h"
#include "room.h"
#include "chapter.h"

using namespace std;

class  gamestate {
public:
	vector<art> artl;
	vector<string> inventory;
	vector<chapter> Chapters;

	chapter Crntchapter;
	room position;

	void play_game();
	void play_room(room room);
	room get_room(string name);
	void addToRoom(string room, object obj);
	void subFromRoom(string room, string name);
	void select_Object(object object);
	void read_art(string file);
	
	void dump_chapter();
	void dump_art();

	void draw_art(string name) {
		for (int i = 0; i < artl.size(); i++)
		{
			if (artl.at(i).name == name)
			{
				artl.at(i).draw();
				
			}
		}
	}
	void brake() {
		cout << "any caricter to continue: ";
		char input;
		cin >> input;
	}

	void line() {
		cout << "--------------------------" << endl;
	}

private:
};

void gamestate::read_art(string file) {
	
	vector<string> art_contence ;
	string art_name = "";

	string line;
	ifstream myfile(file);
	int number = 0;
	while (getline(myfile, line)) {
		if (number == 0)
		{
			artl.push_back(art(art_name,art_contence));
			art_contence = {};
			art_name = "";
			for (int i = 0; i < line.size(); i++)
			{
				if (line.at(i) == ':')
				{
					string get = "";
					for (int j = i+1; j < line.size(); j++)
					{
						get.push_back(line.at(j));
					}
					number = stoi(get);
					i = line.size();
				}
				else
				{
					art_name.push_back(line.at(i));
				}
			}
		}
		else
		{
			art_contence.push_back(line);
			number--;
		}
	}
	artl.push_back(art(art_name, art_contence));
}



void gamestate::play_game()
{
	system("CLS");
	draw_art(position.draw);
	play_room(position);
	line();
	brake();
}

void gamestate::play_room(room room) {
	if (position.name == room.name)
	{
		char input = '_';
		int option = -1;
		//cout << room.objects.size();
		while (option <1 || option >= room.objects.size()+1)
		{
			for (size_t i = 0; i < room.objects.size(); i++)
			{
				cout << i + 1 << room.objects[i].name << endl;
			}
			cout << "select item: ";

			cin >> input;

			option = int(input) -48;
			
			if (input == 'd')
			{
				system("CLS");
				dump_chapter();
				line();
				brake();
				input = 0;

				system("CLS");
				draw_art(position.draw);
			}

			if (input == 'a')
			{
				system("CLS");
				dump_art();
				line();
				brake();
				input = 0;

				system("CLS");
				draw_art(position.draw);
			}
		}
		continueroom:
		select_Object(room.objects.at(option-1));
	}
}

room gamestate::get_room(string name) {
	for (size_t i = 0; i < Crntchapter.rooms.size(); i++)
	{
		//cout << location[i].name << " " << name << " ";
		if (name == Crntchapter.rooms[i].name) {
			return(Crntchapter.rooms[i]);
		}
	}
	return(position);
}


void gamestate::addToRoom(string room, object obj) {
	//cout << " " + room + " ";
	for (size_t i = 0; i < Crntchapter.rooms.size(); i++)
	{
		if (room == Crntchapter.rooms[i].name) {
			Crntchapter.rooms[i].objects.push_back(obj);
		}
	}
}

void gamestate::subFromRoom(string room, string name) {
	for (size_t i = 0; i < Crntchapter.rooms.size(); i++)
	{
		if (room == Crntchapter.rooms[i].name) {
			Crntchapter.rooms[i].remove_object('>' + name);
			//cout << "test1" << endl;
		}
	}
}
 
void gamestate::select_Object(object obj) {
	//cout << endl << actionlist.size();
	//cout << endl << object.actionlist[0] << endl;
	for (size_t i = 1; i < obj.actionlist.size(); i++)
	{
		//action identifier
		char action = obj.actionlist[i][0];
		//action data
		string output = "";
		int index = 0;
		bool flag = false;

		//cout << object.actionlist[i] << endl;
		switch (action) {
		case '&': //draw art
			draw_art(obj.actionlist[i].substr(1));
		break;
		case '^': //add item to 'invantory'
			flag = false;
			output = obj.actionlist[i].substr(1);
			for (size_t j = 0; j < inventory.size(); j++)
			{
				if (inventory[j] == output)
				{
					flag = true;
				}
			}

			if (!flag) {
				inventory.push_back(output);
				//cout << "you pickup " << output << endl;
			}

		break;
		case '?': //if branch
			flag = false;
			index = obj.actionlist[i].rfind(',');
			output = obj.actionlist[i].substr(1,index-1);
			//cout << output << " ";
			for (size_t j = 0; j < inventory.size(); j++)
			{
				//cout << inventory[j] << endl;
				if (inventory[j] == output)
				{
					flag = true;
				}
			}

			//cout << flag << endl;
			if (flag)
			{
				//cout << object.actionlist[i].substr(index+1) << " ";
				for (size_t j = 0; j < position.hidenObjects.size(); j++)
				{
					//cout << position.hidenObjects[j].name;
					if (position.hidenObjects[j].name.substr(1) == obj.actionlist[i].substr(index + 1))
					{
						select_Object(position.hidenObjects[j]);
					}
				}
				return;
			}
			
		break;
		case '!': // adds a brake
			brake();
		break;
		case '<':

		break;
		case '@': //change location
			output.clear();
			output = obj.actionlist[i].substr(1);
			position = get_room(output);
			//draw_art(position.draw);
			i = obj.actionlist.size();
		break;
		case '-': //removes an object from a room
			index = obj.actionlist[i].rfind(',');
			output = obj.actionlist[i].substr(1, index - 1);

			subFromRoom(output, obj.actionlist[i].substr(index + 1));

			cout << output << endl << obj.actionlist[i].substr(index + 1) << endl;
			//cout << output.substr(index + 1);
		break;
		case '+': //adds an object to a room
			//cout << "test2";
			index = obj.actionlist[i].rfind(',');
			output = obj.actionlist[i].substr(1, index - 1);
			
			for (size_t j = 0; j < position.hidenObjects.size(); j++)
			{
				if (position.hidenObjects[j].name.substr(1) == obj.actionlist[i].substr(index + 1))
				{
					addToRoom(output, position.hidenObjects[j]);
				}
			}
			
		break;
		default: //plantext output
			output = obj.actionlist[i];
			cout << output << endl;
			break;
		}
	}
}

void gamestate::dump_chapter() {
	Crntchapter.dump_chapter();
}

void gamestate::dump_art() {
	for(art drawing: artl)
	{
		drawing.draw();
	}
}