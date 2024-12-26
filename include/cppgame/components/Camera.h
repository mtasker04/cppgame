#pragma once

#include <cppgame/Generic.h>
#include <cppgame/components/Component.h>

class Camera : public Component
{
public:
	CPPGAPI Camera(GameObject& obj, float zoom = 1);

	CPPGAPI void Use();

	CPPGAPI void SetZoom(float zoom);
	CPPGAPI float GetZoom() const;

	void Update() override;

private:
	float m_Zoom;

	const float m_MinZoom = 0.1f;
	const float m_MaxZoom = 50.0f;
};