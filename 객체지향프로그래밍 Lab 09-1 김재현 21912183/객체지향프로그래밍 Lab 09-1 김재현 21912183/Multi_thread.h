/* Multi_thread.h */
#ifndef MULTI_THREAD_H
#define MULTI_THREAD_H
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <process.h>
#include <string>
#include "HeapPrioQ_CS.h"
#include "Event.h"
#include "SimParams.h"
using namespace std;
enum ROLE { EVENT_GENERATOR, EVENT_HANDLER };
enum THREAD_FLAG { INITIALIZE, RUN, TERMINATE };

typedef struct ThreadStatusMonitor		// Thread Status Monitor
{
	int numEventGenerated;
	int numEventProcessed;
	int totalEventGenerated;
	int totalEventProcessed;
	Event eventGenerated[TOTAL_NUM_EVENTS];
	Event eventProcessed[TOTAL_NUM_EVENTS];
	THREAD_FLAG* pFlagThreadTerminate;
}ThreadStatusMonitor;

typedef struct ThreadParam				// Thread Parameter
{
	mutex* pCS_main;
	mutex* pCS_thrd_mon;
	HeapPrioQ_CS<int, Event>* pPriQ_Event;
	FILE* fout;
	ROLE role;
	int myAddr;
	int maxRound;
	int targetEventGen;
	LARGE_INTEGER QP_freq;
	ThreadStatusMonitor* pThrdMon;
}ThreadParam_Event;

void EventGen(ThreadParam_Event* pParam);
void EventProc(ThreadParam_Event* pParam);

#endif