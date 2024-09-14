#pragma once
#include <iostream>

using namespace std;

class art {
public:
	string name;
	art() {

	}
	art(string get_name, vector<string> get_contence) {
		name = get_name;
		contence = get_contence;
	}
	void draw() {
		cout << endl;
		for (size_t i = 0; i < contence.size(); i++)
		{
			cout << contence[i] << endl;
		}
	}
private:
	vector<string> contence;
};