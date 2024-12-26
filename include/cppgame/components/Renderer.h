#pragma once

#include <cppgame/Generic.h>
#include <cppgame/Math.h>
#include <cppgame/rendering/Shader.h>
#include <cppgame/types/Color.h>
#include <cppgame/components/Component.h>

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