#include "ShootState.h"
#include <iostream>

ShootState::ShootState() { }
ShootState::~ShootState() { }

void ShootState::onEnter()
{
}

void ShootState::execute()
{
	std::cout << "AI Shooting!" << endl;
}

void ShootState::onExit()
{
}