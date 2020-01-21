#include "../includes_usr/constants.h"
#include "../includes_usr/dispatcher.h"
#include "../includes_usr/file_io.h"
#include "../includes_usr/joblist.h"
#include "../includes_usr/logger_single_thread.h"
#include <queue>

using namespace std;

queue<PCB> readyQ;
queue<PCB> blockedQ;
PCB runningPCB;

//Helper method to clear a queue
void clearQ(queue<PCB> &q) {
	queue<PCB> empty;
	swap(q, empty);
}

//clears ready_Q and blocked_Q these are queues of PCB structures,
//initializes runningPCB to default values in constants (see PCB structure)
void dispatcher::init() {
	clearQ(readyQ);
	clearQ(blockedQ);

	runningPCB.process_number = UNINITIALIZED;
	runningPCB.start_time = UNINITIALIZED;
	runningPCB.cpu_time = UNINITIALIZED;
	runningPCB.io_time = UNINITIALIZED;
}

//used for testing, return a copy of runningPCB
PCB dispatcher::getCurrentJob() {
	return runningPCB;
}

//add a job to the ready queue
void dispatcher::addJob(PCB &myPCB) {
	readyQ.push(myPCB);
}

//interrupt can be either;
//a switch process interrupt in which case the function performs the appropriate tasks and returns PCB_SWITCHED_PROCESSES
//or a io_complete interrupt in which case it pulls ALL processes off of the blockedQ and returns either PCB_MOVED_FROM_BLOCKED_TO_READY (if there were any)
//or PCB_BLOCKED_QUEUE_EMPTY if there were none.
int dispatcher::processInterrupt(int interrupt) {
	if (interrupt == SWITCH_PROCESS) {
		if (readyQ.empty()) {
			if (blockedQ.empty()) {
				return NO_JOBS;
			}
			return BLOCKED_JOBS;
		}

		PCB tempPCB = readyQ.front();
		readyQ.pop();

		if (runningPCB.process_number != UNINITIALIZED) {
			readyQ.push(runningPCB);
		}

		runningPCB = tempPCB;
		return PCB_SWITCHED_PROCESSES;
	}

	else if (interrupt == IO_COMPLETE) {
		if (blockedQ.size() == 0) {
			return PCB_BLOCKED_QUEUE_EMPTY;
		}

		while (!blockedQ.empty()) {
			readyQ.push(blockedQ.front());
			blockedQ.pop();
		}
		return PCB_MOVED_FROM_BLOCKED_TO_READY;
	}

	return PCB_UNIMPLEMENTED;
}

//see flowchart
int dispatcher::doTick() {
	if (runningPCB.process_number == UNINITIALIZED) {
		if (readyQ.empty()) {
			if (blockedQ.empty()) {
				return NO_JOBS;
			}
			return BLOCKED_JOBS;
		}
		runningPCB = readyQ.front();
		readyQ.pop();
		return PCB_MOVED_FROM_READY_TO_RUNNING;
	}
	runningPCB.cpu_time--;

	cout << runningPCB.cpu_time << endl;
	if (runningPCB.cpu_time != 0) {
		return PCB_CPUTIME_DECREMENTED;
	}

	if (runningPCB.io_time == 1) {
		blockedQ.push(runningPCB);
		runningPCB = readyQ.front();
		readyQ.pop();
		return PCB_ADDED_TO_BLOCKED_QUEUE;
	}
	runningPCB = readyQ.front();
	readyQ.pop();
	return PCB_FINISHED;
}
