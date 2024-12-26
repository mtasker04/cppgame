#pragma once

#include <cppgame/Generic.h>
#include <cppgame/IHeapManaged.h>

_INTERNAL class Updatable : public IHeapManaged
{
public:
	Updatable();

	virtual void Start() {}
	virtual void Update() {}
	virtual void Render() {}

public:
	CPPGAPI void Register() override;
};