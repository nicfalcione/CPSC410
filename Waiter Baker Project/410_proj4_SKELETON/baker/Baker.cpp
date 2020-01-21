/**
 * Baker.cpp
 *
 * Author: Nic Falcione & Griffin Hines
 */

#include <mutex>

#include "../includes/baker.h"
#include "../includes/externs.h"
using namespace std;

Baker::Baker(int id) :
		id(id) {
}

Baker::~Baker() {
}

//bake, box and append to anOrder.boxes vector
//if order has 13 donuts there should be 2 boxes
//1 with 12 donuts, 1 with 1 donut
void Baker::bake_and_box(ORDER &anOrder) {
	int num_donuts = anOrder.number_donuts;
	Box box;
	DONUT d;

	for (int i = 0; i < num_donuts; i++) {
		box.addDonut(d);
		if (box.size() == DOZEN) {
			anOrder.boxes.push_back(box);
			box.clear();
		}
	}
	if (box.size() > 0) {
		anOrder.boxes.push_back(box);
	}
}

//as long as there are orders in order_in_Q then
//for each order:
//	create box(es) filled with number of donuts in the order
//  then place finished order on order_outvector
//  if waiter is finished (b_WaiterIsFinished) then
//  finish up remaining orders in order_in_Q and exit
//
//You will use cv_order_inQ to be notified by waiter
//when either order_in_Q.size() > 0 or b_WaiterIsFinished == true
//hint: wait for something to be in order_in_Q or b_WaiterIsFinished == true
void Baker::beBaker() {
	ORDER o;
	while (!b_WaiterIsFinished || !order_in_Q.empty()) {
		o = order_in_Q.front();

		unique_lock<mutex> lock(mutex_order_inQ);
		while (!b_WaiterIsFinished && order_in_Q.empty()) {
			cv_order_inQ.wait(lock);
		}
		if (!order_in_Q.empty()) {
			bake_and_box(o);
			unique_lock<mutex> lockTwo(mutex_order_outQ);
			order_out_Vector.push_back(o);
			order_in_Q.pop();
			cv_order_inQ.notify_all();
		}
	}
}
