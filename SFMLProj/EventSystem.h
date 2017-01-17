#pragma once
#include <string>
#include "BaseEvent.h"
#include <map>
#include <vector>

// Signals lib
#include "Delegate.h"
using namespace Gallant;

class EventReceiver;

class EventSystem
{
public:
	EventSystem();
	~EventSystem();

	// adds a receiver, which notifies you when a certain event type is invoked
	EventReceiver* addReceiver(const std::string id, Delegate1<BaseEvent*> del);

	// invokes an event, notifying all known receivers
	void invokeEvent(const std::string id, BaseEvent* param);

private:
	std::map<std::string, std::vector<EventReceiver*>> _eventMap;

};