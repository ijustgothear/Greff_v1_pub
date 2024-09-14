#pragma once
#include <vector>
#include <list>
#include <iostream>
#include <sstream>
#include "room.h"

using namespace std;

class chapter
{
public:
	string name;
	vector<room> rooms;

	chapter(string file) {
		vector<string> room_contence;

		string line;
		ifstream myfile(file);
		while (getline(myfile, line))
		{
			room_contence.push_back(line);
			if (line.length() > 0) {
				if (line.at(0) == '/')
				{
					if (room_contence.size() > 1)
					{
						rooms.push_back(room(room_contence));
					}
					room_contence.clear();
					room_contence.push_back(line);
				}
			}
		}
		rooms.push_back(room(room_contence));
	}

	void dump_chapter()
	{
		system("CLS");
		for (room obj: rooms)
		{
			cout << obj.name << '\n';
			cout << obj.draw << '\n';
			for (object obje : obj.objects) {
				cout << obje.name << '\n';
			}
		}
	}


private:
};
