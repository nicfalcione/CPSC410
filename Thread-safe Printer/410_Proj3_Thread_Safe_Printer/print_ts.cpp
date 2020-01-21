/*
 * print_ts.cpp
 *
 *  Created on: Feb 26, 2019
 *      Author: Nic Falcione
 */
#include "print_ts.h"

#include <mutex>
#include <iostream>

using namespace std;

mutex m;

//create threadsafe implementations of the following functions
//example
//string s1 = "t";
//string s2 = "s";
//PRINT2(s1,s2);
//PRINT3(s1,s2,s1);0
//should output
//ts
//tst
void PRINT1(std::string &txt) {
	lock_guard<mutex> guard(m);
	cout << txt << endl;
}
void PRINT2(std::string &txt, std::string &txt1) {
	lock_guard<mutex> guard(m);
	cout << txt << txt1 << endl;
}
void PRINT3(std::string &txt, std::string &txt1, std::string &txt2) {
	lock_guard<mutex> guard(m);
	cout << txt << txt1 << txt2 << endl;
}
void PRINT4(std::string &txt, std::string &txt1, std::string &txt2,
		std::string &txt3) {
	lock_guard<mutex> guard(m);
	cout << txt << txt1 << txt2 << txt3 << endl;
}
void PRINT5(std::string &txt, std::string &txt1, std::string &txt2,
		std::string &txt3, std::string &txt4) {
	lock_guard<mutex> guard(m);
	cout << txt << txt1 << txt2 << txt3 << txt4 << endl;
}
