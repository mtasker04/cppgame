#include <cppgame/rendering/VBO.h>

VBO::VBO()
: m_ID(0) {}
VBO::VBO(GLfloat* data, GLsizeiptr size) {
	glGenBuffers(1, &m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VBO::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}
void VBO::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void VBO::Delete() const {
	glDeleteBuffers(1, &m_ID);
}