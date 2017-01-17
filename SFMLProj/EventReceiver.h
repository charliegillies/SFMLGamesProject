#pragma once
#include "BaseEvent.h"
#include "Delegate.h"
#include "Signal.h"
using namespace Gallant;

class EventReceiver
{
public:
	explicit EventReceiver(Delegate1<BaseEvent*> e);
	~EventReceiver();

	void invoke(BaseEvent* e);

private:
	Signal1<BaseEvent*> signal;
};
