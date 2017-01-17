#include "EventReceiver.h"

EventReceiver::EventReceiver(Delegate1<BaseEvent*> e)
{
	this->signal.Connect(e);
}

EventReceiver::~EventReceiver() {}

void EventReceiver::invoke(BaseEvent* e)
{
	// invoke signal
	signal(e);
}
