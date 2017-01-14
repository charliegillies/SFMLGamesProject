#pragma once

/*
	Base type for events.
	Events are represented by a string id
	and they contain composite data that allows
	multiple objects/nodes to communicate without
	knowing about each other.
*/
class BaseEvent
{
public:
	BaseEvent() { }
	virtual ~BaseEvent() { }
};