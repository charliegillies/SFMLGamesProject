#include "EventSystem.h"
#include "EventReceiver.h"

EventSystem::EventSystem() : _eventMap() {}
EventSystem::~EventSystem() {}

EventReceiver* EventSystem::addReceiver(const std::string id, Delegate1<BaseEvent*> del)
{
	// create a new receiver
	EventReceiver* rec = new EventReceiver(del);
	// try and get the vector of receivers
	std::vector<EventReceiver*>& all_rec = _eventMap[id];
	// add this receiver in
	all_rec.push_back(rec);

	return rec;
}

void EventSystem::invokeEvent(const std::string id, BaseEvent* param)
{
	// try and get the vector of receivers
	std::vector<EventReceiver*>& all_rec = _eventMap[id];

	// invoke all receivers with the given parameter
	for (auto i = all_rec.begin(); i != all_rec.end(); ++i)
		(*i)->invoke(param);
}