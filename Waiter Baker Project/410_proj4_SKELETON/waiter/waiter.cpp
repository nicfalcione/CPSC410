/**
 * Waiter.cpp
 *
 * Author: Nic Falcione & Griffin Hines
 */

#include <string>
#include "stdlib.h"

#include "../includes/waiter.h"
#include "../includes/externs.h"
#include "../includes/logger.h"

using namespace std;

Waiter::Waiter(int id, std::string filename) :
		id(id), myIO(filename) {
}

Waiter::~Waiter() {
}

//gets next Order from file_IO
//if return == SUCCESS then anOrder
//contains new order
//otherwise return contains fileIO error
int Waiter::getNext(ORDER &anOrder) {
	return myIO.getNext(anOrder);
}

//contains a loop that will get orders from filename one at a time
//then puts them in order_in_Q then signals baker(s) using cv_order_inQ
//so they can be consumed by baker(s)
//when finished exits loop and signals baker(s) using cv_order_inQ that
//it is done using b_WaiterIsFinished
void Waiter::beWaiter() {
	ORDER o;

	while (getNext(o) == SUCCESS) {
		unique_lock<mutex> lock(mutex_order_inQ);
		order_in_Q.push(o);
		cv_order_inQ.notify_all();
	}

	unique_lock<mutex> lock(mutex_order_inQ);
	b_WaiterIsFinished = true;
	cv_order_inQ.notify_all();
}

