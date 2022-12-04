/*Event.cpp*/
#include "Event.h"

ostream& operator<<(ostream& fout, const Event& evt)					// operation overloading <<
{
	fout << "Event(pri:" << setw(3) << evt.event_pri << ", gen:" << setw(3) << evt.event_gen_addr;
	fout << ", no:" << setw(3) << evt.event_no << ")";
	return fout;
}

Event::Event()															// defualt constructor
{

	event_no = -1;
	event_gen_addr = -1;
	event_handler_addr = -1;
	event_pri = -1;
	eventStatus = GENERATED;
	t_elapsed_time_ms = 0.0;
}

Event::Event(int evt_no, int evt_pri, int evtGenAddr)					// constructor
{
	event_no = evt_no;
	event_gen_addr = evtGenAddr;
	event_handler_addr = -1;
	event_pri = evt_pri;
	eventStatus = GENERATED;
	t_elapsed_time_ms = 0.0;
}

void Event::printEvent_gen()											// printout generated Event
{
	cout << "Ev(no:" << setw(2) << event_no << ", pri:" << setw(2) << event_pri << ") ";
	//cout.precision(2);
	//cout.setf(ios::fixed);
	//cout << ", t_elapsed:" << setw(8) << t_elapsed_time_ms << ") ";
}

void Event::printEvent_proc()											// printout processed Event
{
	cout << "Ev(no:" << setw(2) << event_no << ", pri:" << setw(2) << event_pri;
	cout.precision(2);
	cout.setf(ios::fixed);
	cout << ", t_elapsed:" << setw(8) << t_elapsed_time_ms << ") ";
}


Event* genRandEvent(int evt_no)											// Random Event Generator
{
	Event* pEv;
	int evt_prio;
	int evt_generator_id;
	evt_prio = rand() % MAX_EVENT_PRIORITY;								// Random Priority
	evt_generator_id = rand() % NUM_EVENT_GENERATORS;					// Random Id
	pEv = (Event*) new Event(evt_no, evt_prio, evt_generator_id);
	return pEv;
}

