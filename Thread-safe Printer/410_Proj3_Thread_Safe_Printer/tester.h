/*
 * tester.h,
 *
 *  Created on: Mar 9, 2018
 *      Author: keith
 */

#ifndef TESTER_H_
#define TESTER_H_

#include <string>

enum WHICH_PRINT {
	P1, P2, P3, P4, P5
};
const std::string USER_CHOSE_TO_CANCEL = "User Chose To Cancel";

/*
 * starts cancelable threads
 * string s			-the string to print
 * numThreads 		-the number of threads to start
 * wp 				-which print statement should be used
 * numTimesToPrint 	-the number of PRINT statements each thread will call
 * millisecond_delay- how long (in milliseconds) to wait between prints
 */
void startThreads(std::string s, int numThreads, WHICH_PRINT wp,
		int numTimesToPrint, int millisecond_delay);

/*
 * if bCanceled== true then causes all running threads to print USER_CHOSE_TO_CANCEL and then exit
 * if false then just reset logic used to cancel threads
 */
void setCancelThreads(bool bCancel);

/*
 * waits for all threads to complete
 */
void joinThreads();

#endif /* TESTER_H_ */
