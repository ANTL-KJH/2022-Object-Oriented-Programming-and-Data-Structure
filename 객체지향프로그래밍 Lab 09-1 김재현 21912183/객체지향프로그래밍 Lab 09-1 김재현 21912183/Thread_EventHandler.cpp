/*Thread_EventHandler.cpp*/
#include <Windows.h>
#include "Multi_Thread.h"
#include "HeapPrioQ_CS.h"
#include "Event.h"
using namespace std;
using std::this_thread::sleep_for;

void EventProc(ThreadParam_Event* pParam)
{
	ThreadParam_Event* pThrdParam;
	HeapPrioQ_CS<int, Event>* pPriQ_Event;
	int myRole, myAddr, maxRound;
	THREAD_FLAG* pFlagThreadTerminate;
	T_Entry<int, Event>* pEntry;
	Event event, * pEvent, * pEventProc;
	int event_no = 0, eventPriority = 0, event_gen_count = 0, num_pkt_processed = 0, targetEventGen;
	LARGE_INTEGER QP_freq, t_gen, t_proc;
	LONGLONG t_diff;
	double elapsed_time;
	ThreadStatusMonitor* pThrdMon;

	pThrdParam = (ThreadParam_Event*)pParam;				// Copy Parameter
	myRole = pThrdParam->role;
	myAddr = pThrdParam->myAddr;
	pPriQ_Event = pThrdParam->pPriQ_Event;
	pThrdMon = pThrdParam->pThrdMon;
	maxRound = pThrdParam->maxRound;
	QP_freq = pThrdParam->QP_freq;
	targetEventGen = pThrdParam->targetEventGen;

	for (int round = 0; round < maxRound; round++)
	{
		if (*pThrdMon->pFlagThreadTerminate == TERMINATE)		// Thread Flag check
			break;
		if (!pPriQ_Event->isEmpty())
		{
			pEntry = pPriQ_Event->removeHeapMin();				// remove Min Value
			event = pEntry->getValue();
			pThrdParam->pCS_thrd_mon->lock();					// mutex lock
			//pThrdMon->ppEventsg[pThrdMon->numEventProcs] = pEvent;
			event.setEventHandlerAddr(myAddr);

			QueryPerformanceCounter(&t_proc);					// check count
			event.setEventProcTime(t_proc);						// set proc time
			t_gen = event.getEventGenTime();
			t_diff = t_proc.QuadPart - t_gen.QuadPart;			// calc diff
			elapsed_time = ((double)t_diff / QP_freq.QuadPart);	// elapsed time
			event.setEventElaspsedTime(elapsed_time * 1000);	// set elapsed time

			pThrdMon->eventProcessed[pThrdMon->totalEventProcessed] = event;
			pThrdMon->numEventProcessed++;
			pThrdMon->totalEventProcessed++;
			pThrdParam->pCS_thrd_mon->unlock();					// mutex unlock
		}
		sleep_for(std::chrono::milliseconds(100 + rand() % 50));
		//Sleep(100 + rand() % 300);
	}
}