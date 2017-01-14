#pragma once
#include <string>
#include "BaseEvent.h"
#include <map>
#include <vector>

class EventReceiver;

class EventSystem
{
public:
	EventSystem();
	~EventSystem();

	EventReceiver* addReceiver(const std::string id, void (*receiver) (BaseEvent*));

	void invokeEvent(const std::string id, BaseEvent* param);

private:
	std::map<std::string, std::vector<EventReceiver*>> _eventMap;

};