#pragma once

#include <Generic.h>

#include <IHeapManaged.h>

class Updatable : public IHeapManaged
{
public:
	Updatable();

	virtual void Start() {}
	virtual void Update() {}
	virtual void Render() {}

public:
	void Register() override;
};