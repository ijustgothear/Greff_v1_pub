#pragma once
#include <iostream>
#include <vector>
#include "object.h"
#include "art.h"

using namespace std;

class room {
public:
	string name;
	string draw;
	vector<object> objects;
	vector<object> hidenObjects;

	room(vector<string> room) {
		cout << room.size();

		string getname = room.at(0);
		for (size_t i = 1; i < getname.size(); i++)
		{
			if (getname.at(i) == ':')
			{
				i++;
				for (; i < getname.size(); i++)
				{
					draw.push_back(getname.at(i));
				}
			}
			else
			{
				name.push_back(getname[i]);
			}
		}

		for (size_t i = 1; i < room.size() - 1; i++)
		{
			object getobject = object(room.at(i));
			getobject.room = name;
			if (getobject.name[0] == '>') {
				objects.push_back(getobject);
			}
			else if(getobject.name[0] == '*')
			{
				getobject.name[0] = '>';
				
				hidenObjects.push_back(getobject);
			}
		}
	}
	void remove_object(string name){
		for (int i = 0; i < objects.size(); i++)
		{
			//cout << "test2" << endl;
			if (objects[i].name == name)
			{
				objects.erase(objects.begin() + i);
				//cout << "test2" << endl;
			}
		}
	}

private:

};
