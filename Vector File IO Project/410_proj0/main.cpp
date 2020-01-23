/*
 * main.cpp
 *
 *  Created on: Jan 10, 2019
 *      Author: LilBro
 */
#include <vector>
#include <iostream>
#include <fstream>

#include "utilities.h"

using namespace std;

const string testFile = "testfile.txt";
const string readFile = "readfile.txt";
const string saveFromVectorFile = "output.txt";

bool createReadFile() {
	ofstream file;
	file.open(readFile);

	if (!file.is_open()) {
		return false;
	}

	file
			<< "1,10,51\n2,5,4\n3,3,55\n4,100,53\n5,15,21\n6,0,41\n7,7,11\n8, 1,  19"
			<< endl;
	file.close();
	return true;
}

bool createTesterFile() {
	ofstream file;
	file.open(testFile);

	if (!file.is_open()) {
		return false;
	}

	file << "1,10,51\n2,5,4\n3,3,55\n4,100,53\n5,15,21\n6,0,41\n7,7,11\n8,1,19"
			<< endl;
	file.close();
	return true;
}

void load() {
	loadData(readFile.c_str());
}

void save() {
	saveData(saveFromVectorFile.c_str());
}

bool compareFiles() {
	ifstream file1;
	ifstream file2;
	file1.open(testFile);
	file2.open(saveFromVectorFile);

	if (!file1.is_open() || !file2.is_open()) {
		return false;
	}

	string line1;
	string line2;
	while (!file1.eof() || !file2.eof()) {
		getline(file1, line1);
		getline(file2, line2);

		if (line1 != line2) {
			return false;
		}
	}

	file1.close();
	file2.close();
	return true;
}

int main() {
	createReadFile();
	createTesterFile();

	load();
	save();

	if (compareFiles()) {
		cout << "Good shit!" << endl;
	} else {
		cout << "RIP" << endl;
	}

	sortData(CPU_TIME);
	save();

	sortData(PROCESS_NUMBER);
	save();

	sortData(START_TIME);
	save();
}

