#include <rendering/RenderObject.h>

#include <Debug.h>
#include <Engine.h>
#include <GridSystem.h>
#include <GTime.h>
#include <rendering/GameRenderer.h>
#include <rendering/Texture.h>

#include <vector>

RenderObject::RenderObject(GLfloat* vertices, GLuint* indices, GLsizeiptr vCount, GLsizeiptr iCount, GLint stride, GLint offset, Shader shader) {
	m_Shader = shader;
	CGLOG("[RenderObject] Creating VAO");
	m_VAO = VAO(true);
	CGLOG("[RenderObject] Binding VAO");
	m_VAO.Bind();

	// RenderObject handles conversion from world units to normalized device coordinates
	size_t verticiesCount = vCount / sizeof(GLfloat);
	for (size_t i = offset; i < verticiesCount; i += stride) {
		vertices[i] = GridSystem::PCScale2NPCScale(GridSystem::GridScale2PCScale(vertices[i]), false				/* X */);
		vertices[i + 1] = GridSystem::PCScale2NPCScale(GridSystem::GridScale2PCScale(vertices[i + 1]), true			/* Y */);
	}

	// RenderObject also handles vertex offsets based on the position of the camera
	Camera* camera = Engine::GetCurrentCamera();
	if (camera != nullptr) {
		Vector2 cameraPosition = camera->GetGameObject().GetTransform().position;
		for (size_t i = offset; i < verticiesCount; i += stride) {
			vertices[i] -= GridSystem::PCScale2NPCScale(GridSystem::GridScale2PCScale(cameraPosition.x), false		/* X */);
			vertices[i + 1] -= GridSystem::PCScale2NPCScale(GridSystem::GridScale2PCScale(cameraPosition.y), true	/* Y */);
		}
	}

	CGLOG("[RenderObject] Creating VBO and EBO");
	m_VBO = VBO(vertices, vCount);
	m_EBO = EBO(indices, iCount);

	CGLOG("[RenderObject] Linking VBO");
	m_VAO.LinkAttribPointer(m_VBO, 0, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)0);
	m_VAO.LinkAttribPointer(m_VBO, 1, 4, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	m_VAO.LinkAttribPointer(m_VBO, 2, 2, GL_FLOAT, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	m_VAO.Unbind();

	m_VBO.Unbind();
	m_EBO.Unbind();

	CGLOG("RenderObject created successfully");
}

void RenderObject::Draw() {
	time_point_t start = Time::GetTime();
	CGLOG("[RenderObject] Drawing object");
	m_Shader.Use();
	CGLOG("[RenderObject] Binding VAO");
	m_VAO.Bind();
	CGLOG("[RenderObject] Drawing elements");
	glDrawElements(GL_TRIANGLES, m_EBO.Count(), GL_UNSIGNED_INT, 0);
	m_VAO.Unbind();
	time_point_t end = Time::GetTime();

	float duration = Time::DurationToSeconds(Time::GetDuration(start, end));
	std::ostringstream oss;
	oss << "[RenderObject] Object drawn, took: " << duration << "s";
	CGLOG(oss.str());
}