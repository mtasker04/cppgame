#include <cppgame/components/Camera.h>

#include <cppgame/Math.h>
#include <cppgame/Engine.h>

Camera::Camera(GameObject& obj, float zoom)
	: Component(obj) {
	m_Zoom = Math::Clamp(zoom, m_MinZoom, m_MaxZoom);
}

void Camera::Use() {
	Engine::SetCurrentCamera(this);
}

void Camera::SetZoom(float zoom) {
	m_Zoom = Math::Clamp(zoom, m_MinZoom, m_MaxZoom);
}
float Camera::GetZoom() const {
	return m_Zoom;
}

void Camera::Update() {

}