/*Class_Event.cpp*/
#include "Class_Event.h"

ostream& operator<<(ostream& fout, const Event& evt)					// operation overloading <<
{
	fout << "Event(pri:" << setw(3) << evt.event_pri << ", gen:" << setw(3) << evt.event_gen_addr;
	fout << ", no:" << setw(3) << evt.event_no << ")";
	return fout;
}

Event::Event()															// defualt constructor
{
	event_no = 0;
	event_title = "";
	event_gen_addr = 0;
	event_handler_addr = 0;
	event_pri = 0;
	eventStatus = GENERATED;
}

Event::Event(int event_id, int ev_pri, string title, int gen_addr)		// constructor
{
	event_no = event_id;
	event_pri = ev_pri;
	event_title = title;
	event_gen_addr = gen_addr;
	event_handler_addr = -1;
	eventStatus = GENERATED;
}

void Event::printEvent(ostream& fout)									// printout
{
	fout << "Event(pri:" << setw(3) << event_pri << ", gen:" << setw(3) << event_gen_addr;
	fout << ", no:" << setw(3) << event_no << ")";
}