#pragma once
#include "BaseEvent.h"

class EventReceiver
{
public:
	EventReceiver(void(*receiver)(BaseEvent*));
	~EventReceiver();

	void invoke(BaseEvent* e);

private:
	void(*receiver)(BaseEvent*);
};
