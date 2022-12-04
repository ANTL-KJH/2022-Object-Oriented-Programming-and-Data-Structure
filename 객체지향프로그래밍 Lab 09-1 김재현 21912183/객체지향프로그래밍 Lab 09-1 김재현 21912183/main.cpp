/*
* ������Ʈ�� : "��ü�������α׷��� Lab 09-1 ������ 21912183"
* ���α׷��� ���� �� �⺻ ��� :
* - Multi thread�� �̿��Ͽ� CBT Priority Queue�� ������ �ùķ��̼� �ϴ� ���α׷�
* ���α׷� �ۼ��� : ������(2191283)
* ���� ���α׷� �ۼ��� : 2022.11.07
* ======================================================================================
* ���α׷� ���� / ���� �̷�
* ======================================================================================
* ���α׷� ������			����					����			��������
* JH KIM				2022.11.07			v1.0		���� �ۼ�
* JH KIM				2022.11.08			v1.1		���� ����
* JH KIM				2022.11.09			v1.2		TA_Entry capa ����
*/
#include <time.h>
#include <conio.h>
#include "Event.h"
#include "HeapPrioQ_CS.h"
#include "Class_TA_Entry.h"
#include "SimParams.h"
#include "ConsoleDisplay.h"
#include "Multi_thread.h"

int main(void)
{
	// �۵��� �ʿ��� ���� ����
	HANDLE consHndlr;
	LARGE_INTEGER QP_freq;
	mutex cs_main, cs_thrd_mon;
	double min_elapsed_time, max_elapsed_time;
	double avg_elapsed_time, total_elapsed_time;
	ThreadParam_Event thrdParam_EventHndlr, thrdParam_EventGen;
	int numEventGenerated, num_events_in_PrioQ, numEventProcessed, count;
	ThreadStatusMonitor thrdMon;
	THREAD_FLAG eventThreadFlag = RUN;
	Event* pEvent, * pEv_min_elasped_time = NULL, * pEv_max_elapsed_time = NULL;

	//ofstream fout;
	//fout.open("output.txt");				// file open
	//if (fout.fail())						// ofstream check
	//{
	//	cout << "Fail to open output.txt file for results !!" << endl;
	//	exit(1);
	//}
	
	HeapPrioQ_CS<int, Event> heapPriQ_Event(30, string("HeapPriorityQueue_Event"));		// Gen PriQ
			
	//Event eventProcessed[TOTAL_NUM_EVENTS];
	consHndlr = initConsoleHandler();						// Console Handler
	QueryPerformanceFrequency(&QP_freq);					// Freq check
	srand(time(NULL));

	// init Thread Monitor
	thrdMon.pFlagThreadTerminate = &eventThreadFlag;
	thrdMon.totalEventGenerated = 0;
	thrdMon.totalEventProcessed = 0;
	thrdMon.numEventGenerated = 0;
	thrdMon.numEventProcessed = 0;

	// Thread Parameter - Event Handler
	//thrdParam_EventHndlr.fout = fout;
	thrdParam_EventHndlr.maxRound = MAX_ROUND;
	thrdParam_EventHndlr.myAddr = 0;
	thrdParam_EventHndlr.pCS_main = &cs_main;
	thrdParam_EventHndlr.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventHndlr.pPriQ_Event = &heapPriQ_Event;
	thrdParam_EventHndlr.pThrdMon = &thrdMon;
	thrdParam_EventHndlr.QP_freq = QP_freq;
	thrdParam_EventHndlr.role = EVENT_HANDLER;
	thrdParam_EventHndlr.targetEventGen = NUM_EVENTS_PER_GEN;

	// Thread Parameter - Event Generator
	//thrdParam_EventGen.fout = fout;
	thrdParam_EventGen.maxRound = MAX_ROUND;
	thrdParam_EventGen.myAddr = 0;
	thrdParam_EventGen.pCS_main = &cs_main;
	thrdParam_EventGen.pCS_thrd_mon = &cs_thrd_mon;
	thrdParam_EventGen.pPriQ_Event = &heapPriQ_Event;
	thrdParam_EventGen.pThrdMon = &thrdMon;
	thrdParam_EventGen.QP_freq = QP_freq;
	thrdParam_EventGen.role = EVENT_GENERATOR;
	thrdParam_EventGen.targetEventGen = NUM_EVENTS_PER_GEN;


	thread thrd_EvProc(EventProc, &thrdParam_EventHndlr);
	cs_main.lock();													// mutex lock for printout
	printf("Thread_EventGen is created and activated ...\n");
	cs_main.unlock();												// mutex unlock
	thread thrd_EvGen(EventGen, &thrdParam_EventGen);				// Gen Multi Thread
	cs_main.lock();													// mutex lock for printout
	printf("Thread_EventGen is created and activated ...\n");
	cs_main.unlock();												// mutex unlock

	for (int round = 0; round < MAX_ROUND; round++)
	{
		cs_main.lock();												// mutex lock for printout
		system("cls");												// cls �۵� Ȯ��(LG Gram, 2021 10, Windosw 11, i5-1135G7, 16GB, Visual Studio 2022
		//cls(consHndlr);											// cls �۵� Ȯ��(LG Gram, 2021 10, Windosw 11, i5-1135G7, 16GB, Visual Studio 2022
		gotoxy(consHndlr, 0, 0);
		printf("Thread monitoring by main() ::\n");
		printf(" round(%2d): current total_event_gen (%2d), total_event_proc(%2d)\n", round, thrdMon.totalEventGenerated, thrdMon.totalEventProcessed);
		printf("\n*****************************\n");
		numEventGenerated = thrdMon.numEventGenerated;
		printf("Events generated (current total = %2d)\n ", numEventGenerated);
		total_elapsed_time = 0.0;
		for (int ev = 0; ev < numEventGenerated; ev++)
		{
			pEvent = &thrdMon.eventGenerated[ev];
			if (pEvent != NULL)
			{
				pEvent->printEvent_gen();
				if (((ev + 1) % EVENT_PER_LINE) == 0)
					printf("\n ");
			}
			if (ev == 0)
			{
				min_elapsed_time = max_elapsed_time = total_elapsed_time = pEvent->getEventElapsedTime(); // in milli-second
				pEv_min_elasped_time = pEv_max_elapsed_time = pEvent;
			}
			else
			{
				if (min_elapsed_time > pEvent->getEventElapsedTime())
				{
					min_elapsed_time = pEvent->getEventElapsedTime(); // in milli-second
					pEv_min_elasped_time = pEvent;
				}
				if (max_elapsed_time < pEvent->getEventElapsedTime())
				{
					max_elapsed_time = pEvent->getEventElapsedTime(); // in milli-second
					pEv_max_elapsed_time = pEvent;
				}
				total_elapsed_time += pEvent->getEventElapsedTime();
			}
		}
    

		printf("\n*****************************\n");
		num_events_in_PrioQ = heapPriQ_Event.size();
		printf("Events currently in Priority_Queue (%d) : \n", num_events_in_PrioQ);
		if (num_events_in_PrioQ == 0)
			cout << "HeapPriorityQueue is Empty!!";
		else
			heapPriQ_Event.fprint(cout);
		printf("\n\n*****************************\n");
		numEventProcessed = thrdMon.totalEventProcessed;
		printf("Events processed (current total = %d): \n ", numEventProcessed);
		//count = 0;
		total_elapsed_time = 0.0;
		for (int ev = 0; ev < numEventProcessed; ev++)
		{
			pEvent = &thrdMon.eventProcessed[ev];
			if (pEvent != NULL)
			{
				pEvent->printEvent_proc();
				if (((ev + 1) % EVENT_PER_LINE) == 0)
					printf("\n ");
			}
			if (ev == 0)
			{
				min_elapsed_time = max_elapsed_time = total_elapsed_time = pEvent->getEventElapsedTime(); // in milli-second
				pEv_min_elasped_time = pEv_max_elapsed_time = pEvent;
			}
			else
			{
				if (min_elapsed_time > pEvent->getEventElapsedTime())
				{
					min_elapsed_time = pEvent->getEventElapsedTime();		// Min_Elapsed_Time
					pEv_min_elasped_time = pEvent;
				}
				if (max_elapsed_time < pEvent->getEventElapsedTime())
				{
					max_elapsed_time = pEvent->getEventElapsedTime();		// Max_Elapsed_Time
					pEv_max_elapsed_time = pEvent;
				}
				total_elapsed_time += pEvent->getEventElapsedTime();		// Total_Elapsed_Time
			}
		}
		cout << endl;
		if (numEventProcessed > 0)
		{
			printf("numEventProcessed = %d\n", numEventProcessed);
			printf("min_elapsed_time = %8.2lf[ms]; ", min_elapsed_time);
			cout << *pEv_min_elasped_time << endl;
			printf("max_elapsed_time = %8.2lf[ms]; ", max_elapsed_time);
			cout << *pEv_max_elapsed_time << endl;
			avg_elapsed_time = total_elapsed_time / numEventProcessed;
			printf("avg_elapsed_time = %8.2lf[ms]; \n", avg_elapsed_time);
		}
		if (numEventProcessed >= TOTAL_NUM_EVENTS)
		{
			eventThreadFlag = TERMINATE;					// Event Processing End
			cs_main.unlock();								// mutex unlock
			break;
		}
		cs_main.unlock();
		Sleep(100);
	}
	thrd_EvProc.join();					// Thread join
	thrd_EvGen.join();					// Thread join
	//fout.close();
	printf("Hit any key to terminate : ");
	_getch();
	return 0;
}