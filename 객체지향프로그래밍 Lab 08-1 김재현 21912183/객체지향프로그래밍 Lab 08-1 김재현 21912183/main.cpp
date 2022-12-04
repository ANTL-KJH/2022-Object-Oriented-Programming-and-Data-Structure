/*
* 프로젝트명 : "객체지향프로그래밍 Lab 08-1 김재현 21912183"
* 프로그램의 목적 및 기본 기능 :
* - Complete Binary Tree를 이용한 Heap Priotity Queue를 출력하는 프로그램
* 프로그램 작성자 : 김재현(2191283)
* 최초 프로그램 작성일 : 2022.11.01
* ======================================================================================
* 프로그램 수정 / 보완 이력
* ======================================================================================
* 프로그램 수정자		일자					버전			수정내용
* JH KIM				2022.11.01				v1.0		최초 작성
*/

#include "Class_CompleteBinaryTree.h"
#include "Class_Event.h"
#include "Class_HeapPriQ.h"
#include "Class_TA_Entry.h"
#include "Class_T_Entry.h"
using namespace std;

#define INITIAL_CBT_CAPA 100		// CBT CAPA
#define TEST_HEAP_PRIO_Q_EVENT
#define NUM_EVENTS 15				// EVENT elements
int main(void)
{
	ofstream fout;
	fout.open("output.txt");		// open output file
	if (fout.fail())				// file open check
	{
		cout <<  "Fail to open output.txt file for results !!" << endl;
		exit(1);
	}

	Event events[NUM_EVENTS] =
	{
		// Event data
		Event(0, 14, "evt_00", 0), Event(1, 13, "evt_01", 1), Event(2, 12, "evt_02", 2),
		Event(3, 11, "evt_03", 3), Event(4, 10, "evt_04", 4), Event(5, 9, "evt_05", 5),
		Event(6, 8, "evt_06", 6), Event(7, 7, "evt_07", 7), Event(8, 6, "evt_08", 8),
		Event(9, 5, "evt_09", 9), Event(10, 4, "evt_10", 10), Event(11, 3, "evt_11", 11),
		Event(12, 2, "evt_12", 12), Event(13, 1, "evt_13", 13), Event(14, 0, "evt_14", 14)
	};

	HeapPrioQueue<int, Event*> HeapPriQ_Event(INITIAL_CBT_CAPA,	string("Event_Heap_Priority_Queue"));		// gen HeapPrioQueue Template obejct

	T_Entry<int, Event*> entry_event, * pEntry_Event;														// gen T_Entry Template obejct
	for (int i = 0; i < NUM_EVENTS; i++)
	{
		entry_event.setKey(events[i].getEventPri());				// set key
		entry_event.setValue(&events[i]);							// set value
		HeapPriQ_Event.insert(entry_event);							// insert
		fout << "Insert " << events[i];
		fout << " ==> Size of Heap Priority Queue : " << setw(3) << HeapPriQ_Event.size() << endl;
	}

	fout << "Final status of insertions : " << endl;
	HeapPriQ_Event.fprintCBT_byLevel(fout);							// print out priQ after insert

	for (int i = 0; i < NUM_EVENTS; i++)
	{
		fout << "\nCurrent top priority in Heap Priority Queue : ";
		pEntry_Event = HeapPriQ_Event.getHeapMin();					// get min data from heap priQ
		fout << *pEntry_Event << endl;								// printout event
		pEntry_Event = HeapPriQ_Event.removeHeapMin();				// remove min data at the Heap PriQ
		fout << "Remove " << *pEntry_Event;
		fout << " ==> " << HeapPriQ_Event.size() << " elements remains." << endl;
		HeapPriQ_Event.fprintCBT_byLevel(fout);
		fout << endl;
	}
	fout.close();
	return 0;
}