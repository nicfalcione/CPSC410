/*
 * tester.cpp
 *
 *  Created on: Feb 26, 2019
 *      Author: Nic Falcione
 */
#include "print_ts.h"
#include "tester.h"
#include <mutex>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;

vector<thread> threads;
atomic<bool> doWork(true);
string USER_CHOSE_TO_CANCEL1 = "User Chose To Cancel";

void helper(WHICH_PRINT wp, string s, int times, int millisecond_delay) {
	if (wp == P1) {
		for (int i = 0; i < times; i++) {
			if (doWork) {
				PRINT1(s);
				this_thread::sleep_for(chrono::milliseconds(millisecond_delay));
			} else {
				PRINT1(USER_CHOSE_TO_CANCEL1);
				this_thread::sleep_for(chrono::milliseconds(millisecond_delay));
				break;
			}
		}
	} else if (wp == P2) {
		for (int i = 0; i < times; i++) {
			if (doWork) {
				PRINT2(s, s);
				this_thread::sleep_for(chrono::milliseconds(millisecond_delay));
			} else {
				PRINT1(USER_CHOSE_TO_CANCEL1);
				this_thread::sleep_for(chrono::milliseconds(millisecond_delay));
				break;
			}
		}
	} else if (wp == P3) {
		for (int i = 0; i < times; i++) {
			if (doWork) {
				PRINT3(s, s, s);
				this_thread::sleep_for(chrono::milliseconds(millisecond_delay));
			} else {
				PRINT1(USER_CHOSE_TO_CANCEL1);
				this_thread::sleep_for(chrono::milliseconds(millisecond_delay));
				break;
			}
		}
	} else if (wp == P4) {
		for (int i = 0; i < times; i++) {
			if (doWork) {
				PRINT4(s, s, s, s);
				this_thread::sleep_for(chrono::milliseconds(millisecond_delay));
			} else {
				PRINT1(USER_CHOSE_TO_CANCEL1);
				this_thread::sleep_for(chrono::milliseconds(millisecond_delay));
				break;
			}
		}
	} else {
		for (int i = 0; i < times; i++) {
			if (doWork) {
				PRINT5(s, s, s, s, s);
				this_thread::sleep_for(chrono::milliseconds(millisecond_delay));
			} else {
				PRINT1(USER_CHOSE_TO_CANCEL1);
				this_thread::sleep_for(chrono::milliseconds(millisecond_delay));
				break;
			}
		}
	}
}

/*
 * starts cancelable threads
 * string s			-the string to print
 * numThreads 		-the number of threads to start
 * wp 				-which print statement should be used
 * numTimesToPrint 	-the number of PRINT statements each thread will call
 * millisecond_delay- how long (in milliseconds) to wait between prints
 */
void startThreads(std::string s, int numThreads, WHICH_PRINT wp,
		int numTimesToPrint, int millisecond_delay) {
	for (int i = 0; i < numThreads; i++) {
		threads.push_back(
				thread(helper, wp, s, numTimesToPrint, millisecond_delay));
	}
}
/*
 * if bCanceled== true then causes all running threads to print USER_CHOSE_TO_CANCEL and then exit
 * if false then just reset logic used to cancel threads
 */
void setCancelThreads(bool bCancel) {
	doWork = !bCancel;
}

/*
 * waits for all threads to complete
 */
void joinThreads() {
	for (auto& thread : threads) {
		thread.join();
	}
}
