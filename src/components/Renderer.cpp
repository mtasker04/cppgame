#include <components/Renderer.h>

#include <Debug.h>
#include <Engine.h>
#include <GameObject.h>
#include <rendering/GameRenderer.h>
#include <rendering/RenderObject.h>

#include <glad/glad.h>

Renderer::Renderer(GameObject& obj, RendererMode mode)
	: Component(obj), rendererMode(mode), m_Texture(nullptr), m_Shader(nullptr) {
	// TEMPORARY
	m_Shader = new Shader(R"(rendering\shaders\default.vert)", R"(rendering\shaders\default.frag)");
}
Renderer::~Renderer() {
	delete m_Shader;
}

void Renderer::SetTexture(Texture* texture) {
	m_Texture = texture;
	m_Shader->SetTexture(0, texture);
}
Texture* Renderer::GetTexture() const {
	return m_Texture;
}

void Renderer::SetShader(Shader* shader) {
	m_Shader = shader;
}
Shader* Renderer::GetShader() const {
	return m_Shader;
}

void Renderer::Render() {
	Transform& transform = gameObject.GetTransform();
	if (rendererMode == RendererMode::Rect) {
		CGLOG("[Renderer] Rendering rect");
		float hWidth = transform.scale.x / 2;
		float hHeight = transform.scale.y / 2;

		Vector2 position = transform.position;

		GLfloat vertices[] =
		{   // X                    // Y                    // R     // G     // B     // A         // Tex X        // Tex Y
			// Bottom left vertex
			-hWidth + position.x,   -hHeight + position.y,  color.r, color.g, color.b, color.a,     0.0f,           0.0f,
			// Top left vertex
			-hWidth + position.x,   hHeight + position.y,   color.r, color.g, color.b, color.a,     0.0f,           1.0f,
			// Top right vertex
			hWidth + position.x,    hHeight + position.y,   color.r, color.g, color.b, color.a,     1.0f,           1.0f,
			// Bottom right vertex
			hWidth + position.x,    -hHeight + position.y,  color.r, color.g, color.b, color.a,     1.0f,           0.0f
		};
		//    UV MAP
		//(0,1)		(1,1)
		//(0,0)		(1,0)
		//
		GLuint indices[] =
		{
			0, 1, 2,
			0, 2, 3
		};
		
		CGLOG("[Renderer] Creating RenderObject");
		RenderObject* object = new RenderObject(vertices, indices, sizeof(vertices), sizeof(indices), 8, 0, *m_Shader);
		CGLOG("[Renderer] Binding RenderObject");
		Engine::GetWindow()->GetRenderer()->BindObject(object);
	}
}