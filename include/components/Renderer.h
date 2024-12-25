#pragma once

#include <Generic.h>
#include <GMath.h>
#include <rendering/Shader.h>
#include <types/Color.h>
#include <components/Component.h>

enum class RendererMode
{
	Rect
};
class Renderer : public Component
{
public:
	CPPGAPI Renderer(GameObject& obj, RendererMode mode = RendererMode::Rect);
	~Renderer();

	CPPGAPI void SetTexture(Texture* texture);
	CPPGAPI Texture* GetTexture() const;

	CPPGAPI void SetShader(Shader* shader);
	CPPGAPI Shader* GetShader() const;

	RendererMode rendererMode;
	Color color;

protected:
	void Render() override;

	Texture* m_Texture;
	Shader* m_Shader;
};