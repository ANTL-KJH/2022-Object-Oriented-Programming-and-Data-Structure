/*Class_Event.h*/
#ifndef CLASS_EVENT
#define CLASS_EVENT
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

enum EventStatus{ GENERATED, ENQUEUED, PROCESSED, UNDEFINED };
class Event
{
	friend ostream& operator<<(ostream& fout, const Event& evt);
public:
	Event();														// default constructor
	Event(int event_id, int event_pri, string title, int gen_addr); //constructor
	void printEvent(ostream& fout);
	void setEventHandlerAddr(int evtHndlerAddr) { event_handler_addr = evtHndlerAddr; }
	void setEventGenAddr(int genAddr) { event_gen_addr = genAddr; }
	void setEventNo(int evtNo) { event_no = evtNo; }
	void setEventPri(int pri) { event_pri = pri; }
	void setEventStatus(EventStatus evtStatus) { eventStatus = evtStatus; }
	int getEventPri() { return event_pri; }
	int getEventNo() { return event_no; }
	bool operator>(Event& e) { return (event_pri > e.event_pri); }
	bool operator<(Event& e) { return (event_pri < e.event_pri); }
private:
	int event_no;
	string event_title;
	int event_gen_addr;
	int event_handler_addr;
	int event_pri;
	EventStatus eventStatus;
};

#endif