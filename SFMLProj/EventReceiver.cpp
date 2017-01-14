#include "EventReceiver.h"

EventReceiver::EventReceiver(void(*receiver)(BaseEvent*))
{
	this->receiver = receiver;
}

EventReceiver::~EventReceiver() {}

void EventReceiver::invoke(BaseEvent* e)
{
	// invoke function pointer
	receiver(e);
}
