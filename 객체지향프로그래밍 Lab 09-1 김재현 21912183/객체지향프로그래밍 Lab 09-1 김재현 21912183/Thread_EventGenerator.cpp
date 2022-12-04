/*Thread_EventGenerator.cpp*/
#include <Windows.h>
//#include <chrono>
#include "Multi_Thread.h"
#include "HeapPrioQ_CS.h"
#include "Event.h"
#include "SimParams.h"
#define myExitCode 0
using std::this_thread::sleep_for;

void EventGen(ThreadParam_Event* pParam)					// Event Generator Thread
{
	ThreadParam_Event* pThrdParam;
	HeapPrioQ_CS<int, Event>* pPriQ_Event;
	THREAD_FLAG* pFlagThreadTerminate;
	int maxRound;
	T_Entry<int, Event>* pEntry, entry_event;
	Event event, * pEvent;
	int myRole, event_priority = 0, event_no = 0, myAddr = -1, event_handler_addr, targetEventGen, event_gen_count = 0;
	LARGE_INTEGER QP_freq, t_gen;
	ThreadStatusMonitor* pThrdMon;

	pThrdParam = (ThreadParam_Event*)pParam;				// Copy Parameter
	myRole = pThrdParam->role;
	myAddr = pThrdParam->myAddr;
	pPriQ_Event = pThrdParam->pPriQ_Event;
	pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound;
	targetEventGen = pThrdParam->targetEventGen;

	for (int round = 0; round < maxRound; round++)
	{
		if (event_gen_count >= targetEventGen)
		{
			if (*pThrdMon->pFlagThreadTerminate == TERMINATE)		// Flag check
				break;
			else
			{
				sleep_for(std::chrono::milliseconds(500));
				continue;
			}
		}
		event_no = event_gen_count + NUM_EVENTS_PER_GEN * myAddr;
		event_priority = targetEventGen - event_gen_count - 1;
		event.setEventNo(event_no);
		event.setEventPri(event_priority);
		event.setEventGenAddr(myAddr);
		event.setEventHandlerAddr(-1);

		QueryPerformanceCounter(&t_gen);							// check count
		event.setEventGenTime(t_gen);								// set event gen time

		event.setEventStatus(GENERATED);
		entry_event.setKey(event.getEventPri());
		entry_event.setValue(event);

		while (pPriQ_Event->insert(entry_event) == NULL)
		{
			pThrdParam->pCS_main->lock();
			cout << "PriQ_Event is Full, waiting ..." << endl;
			pThrdParam->pCS_main->unlock();
			sleep_for(std::chrono::milliseconds(100));
			
			//pThrdParam->pCS_main->lock();
			//cout << "Trying to insert an event into PriQ_Event " << endl;
			//pThrdParam->pCS_main->unlock();
			//sleep_for(std::chrono::milliseconds(100));
			
		}

		pThrdParam->pCS_main->lock();								// mutex lock for printout
		cout << "Successfully inserted into PriQ_Event " << endl;
		pThrdParam->pCS_main->unlock();								// mutex unlock
		pThrdParam->pCS_thrd_mon->lock();
		pThrdMon->eventGenerated[pThrdMon->totalEventGenerated] = event;
		pThrdMon->numEventGenerated++;
		pThrdMon->totalEventGenerated++;
		pThrdParam->pCS_thrd_mon->unlock();
		event_gen_count++;
		//Sleep(100 + rand() % 300);
		sleep_for(std::chrono::milliseconds(10));
	}
}