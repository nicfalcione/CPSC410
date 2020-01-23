/*
 * utilities.cpp
 *
 *  Created on: Jan 10, 2019
 *      Author: Nic Falcione
 */
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "utilities.h"

using namespace std;

vector<process_stats> vect;

//allthe functions available for use

//clears vector holding process_stats structs
//attempt to open file 'filename' to read, parse its rows
//into process_stats structs and add these structs to a vector
//
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int loadData(const char* filename) {
	vect.clear();

	ifstream file;
	file.open(filename);

	if (!file.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	while (!file.eof()) {
		process_stats p;

		string line;
		string csv;
		getline(file, line);
		istringstream myline(line);
		int i = 0;

		int process;
		int start;
		int time;

		while (getline(myline, csv, CHAR_TO_SEARCH_FOR)) {
			switch (i) {
			case 0:
				process = stoi(csv);
				i++;
				break;
			case 1:
				start = stoi(csv);
				i++;
				break;

			case 2:
				time = stoi(csv);

				p.process_number = process;
				p.start_time = start;
				p.cpu_time = time;
				vect.push_back(p);

				i = 0;
				break;
			}
		}
	}

	file.close();
	return SUCCESS;
}

//Helper method for serializing data to a file
string statsToString(process_stats &p) {
	return to_string(p.process_number) + "," + to_string(p.start_time) + ","
			+ to_string(p.cpu_time);
}

//attempt to open file 'filename' to write, and serialize a
//vector full of process_stats structs to it.  Should be in the same
//format as original file but not necessarily the same order or length
//if the file exists, overwrite its contents.
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int saveData(const char* filename) {
	ofstream file;
	file.open(filename);

	if (!file.is_open()) {
		return COULD_NOT_OPEN_FILE;
	}

	string line;
	for (unsigned int i = 0; i < vect.size(); i++) {
		file << statsToString(vect[i]) << endl;
	}

	file.close();
	return SUCCESS;
}

//Helper method for sorting process_stats structs
bool compareCPUTime(process_stats a, process_stats b) {
	int aTemp = a.cpu_time;
	int bTemp = b.cpu_time;
	return (aTemp < bTemp);
}

//Helper method for sorting process_stats structs
bool compareProcessNum(process_stats a, process_stats b) {
	int aTemp = a.process_number;
	int bTemp = b.process_number;
	return (aTemp < bTemp);
}

//Helper method for sorting process_stats structs
bool compareStartTime(process_stats a, process_stats b) {
	int aTemp = a.start_time;
	int bTemp = b.start_time;
	return (aTemp < bTemp);
}

//sorts the vector, returns nothing (thats what void means)
//sorts low to high
void sortData(SORT_ORDER mySortOrder) {
	if (mySortOrder == CPU_TIME) {
		sort(begin(vect), begin(vect) + vect.size(), compareCPUTime);
	}

	else if (mySortOrder == PROCESS_NUMBER) {
		sort(begin(vect), begin(vect) + vect.size(), compareProcessNum);
	}

	else {
		sort(begin(vect), begin(vect) + vect.size(), compareStartTime);
	}
}

//return the first struct in the vector
//then deletes it from the vector
process_stats getNext() {
	process_stats p;
	if (vect.size() == 0) {
		return p;
	}
	p = vect[0];
	vect.erase(vect.begin());
	return p;
}

