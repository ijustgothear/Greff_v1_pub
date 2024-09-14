#pragma once
#include <iostream>
#include <vector>
#include "gamestate.h"

using namespace std;

class object {
public:
	object(string init_line)
	{
		name = "";
		string buffer;
		for (int i = 0; i < init_line.size(); i++)
		{
			if (init_line.at(i) == ':')
			{
				actionlist.push_back(buffer);
				buffer = "";
			}
			else
			{
				buffer.push_back(init_line.at(i));
			}
		}
		if (actionlist.size() > 0)
		{
			name = actionlist.at(0);
		}
		actionlist.push_back(buffer);
	}
	string name;
	string room;
	vector<string> actionlist;
private:
};