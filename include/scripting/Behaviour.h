#pragma once

#include <Generic.h>
#include <components/Component.h>
#include <components/Transform.h>

class Behaviour : public Component
{
public:
	CPPGAPI Behaviour(GameObject& obj);
};