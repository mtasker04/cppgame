#pragma once

#include <cppgame/Generic.h>
#include <cppgame/components/Component.h>
#include <cppgame/components/Transform.h>

class Behaviour : public Component
{
public:
	CPPGAPI Behaviour(GameObject& obj);
};