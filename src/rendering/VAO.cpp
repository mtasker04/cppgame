#include <cppgame/rendering/VAO.h>

VAO::VAO(bool gen) {
	m_ID = 0;
	if (gen) {
		glGenVertexArrays(1, &m_ID);
	}
}

void VAO::LinkAttribPointer(VBO& VBO, GLuint layout, GLint size, GLenum type, GLsizei stride, const void* pointer) {
	VBO.Bind();
	glVertexAttribPointer(layout, size, type, GL_FALSE, stride, pointer);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}
void VAO::Bind() {
	glBindVertexArray(m_ID);
}
void VAO::Unbind() {
	glBindVertexArray(0);
}
void VAO::Delete() {
	glDeleteVertexArrays(1, &m_ID);
}