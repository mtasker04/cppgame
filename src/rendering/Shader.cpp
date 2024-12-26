#include <cppgame/rendering/Shader.h>

#include <cppgame/Debug.h>

#include <glad/glad.h>

std::string GetFileContents(const char* path) {
	std::ifstream in(path, std::ios::binary);
	if (in)
	{
		std::string contents;
		in.seekg(0, std::ios::end);
		contents.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&contents[0], contents.size());
		in.close();
		return(contents);
	}
	std::ostringstream oss;
	oss << "Failed to open shader file: " << path;
	CGFATAL(oss.str());
	return "std::nullptr_t";
}

Shader::Shader()
	: m_ID(0), m_ZOrder(0) {}
Shader::Shader(const char* vertPath, const char* fragPath)
	: m_ZOrder(0) {
	std::string vertexCode = GetFileContents(vertPath);
	std::string fragmentCode = GetFileContents(fragPath);

	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	glLinkProgram(m_ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}
Shader::~Shader() {
	
}

void Shader::SetZOrder(int zOrder) {
	m_ZOrder = zOrder;
}
int Shader::GetZOrder() const {
	return m_ZOrder;
}

void Shader::Use() const {
	glUseProgram(m_ID);
	SetUniformInt("_zOrder", m_ZOrder);
	for (unsigned int i = 0; i < m_Textures.size(); i++) {
		m_Textures[i]->Bind(i);
		SetUniformInt(m_Textures[i]->GetName().c_str(), i);
	}
}
void Shader::Delete() const {
	glDeleteProgram(m_ID);
}

void Shader::SetUniformInt(const char* name, int value) const {
	glUniform1i(glGetUniformLocation(m_ID, name), (GLint)value);
}

void Shader::AddTexture(Texture* texture) {
	m_Textures.push_back(texture);
}
void Shader::SetTexture(unsigned int index, Texture* texture) {
	if (index > Texture::GetMaxTextureSlots()) {
		CGFATAL("Texture slot exceeds amount supported by system.");
		return;
	}
	if (index > m_Textures.size()) {
		m_Textures.resize(static_cast<std::vector<Texture*, std::allocator<Texture*>>::size_type>(index) + 1);
	}
	m_Textures[index] = texture;
}
Texture* Shader::GetTexture(unsigned int index) {
	return m_Textures[index];
}
void Shader::RemoveTexture(Texture* texture) {
	m_Textures.erase(std::remove(m_Textures.begin(), m_Textures.end(), texture), m_Textures.end());
}

void Shader::Register()
{
}
