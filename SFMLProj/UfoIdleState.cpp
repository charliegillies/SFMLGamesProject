#include "UfoIdleState.h"

UfoIdleState::UfoIdleState() {}
UfoIdleState::~UfoIdleState() {}

void UfoIdleState::onEnter() { }

// rotate slowly
void UfoIdleState::execute()
{
	stateMachine->nTransform->rotation += 1.0f;
}

void UfoIdleState::onExit() { }
