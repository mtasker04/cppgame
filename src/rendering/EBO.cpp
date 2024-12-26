#include <cppgame/rendering/EBO.h>

EBO::EBO()
: m_ID(0), m_Count(0) {}
EBO::EBO(GLuint* data, GLsizeiptr size) {
	m_Count = (GLsizei)(size / sizeof(GLuint));
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void EBO::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}
void EBO::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void EBO::Delete() const {
	glDeleteBuffers(1, &m_ID);
}

GLsizei EBO::Count() const {
	return m_Count;
}