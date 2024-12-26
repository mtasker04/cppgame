#include <cppgame/rendering/Texture.h>

#include <cppgame/Debug.h>
#include <cppgame/Engine.h>

#include <filesystem>
#include <sstream>
#include <glad/glad.h>
#include <stb_image.h>

Texture::Texture(const std::string& name, const char* path, FilterMode filter, WrapMode verticalWrap, WrapMode horizontalWrap)
	: m_ID(0), m_Name(name), m_Width(0), m_Height(0), m_Channels(0), m_Data(nullptr), m_Path(path), m_FilterMode(filter), m_VerticalWrap(verticalWrap), m_HorizontalWrap(horizontalWrap) {
	Register();

	if (name.find(" ") != std::string::npos) {
		CGFATAL("Texture name cannot contain spaces.");
	}
	if (!std::filesystem::exists(path)) {
		std::ostringstream oss;
		oss << "Failed to create texture, file does not exist: " << path;
		CGFATAL(oss.str());
	}
}
Texture::~Texture() {
	glDeleteTextures(1, &m_ID);
}

void Texture::Init() {
	glGenTextures(1, &m_ID);
	glBindTexture(GL_TEXTURE_2D, m_ID);

	stbi_set_flip_vertically_on_load(true);
	m_Data = stbi_load(m_Path, &m_Width, &m_Height, &m_Channels, 0);
	if (!m_Data) {
		std::ostringstream oss;
		oss << "Failed to load texture: " << m_Path << "\n" << "Reason: ";
		oss << stbi_failure_reason();
		CGFATAL(oss.str());
	}

	GLenum vertWrap = (m_VerticalWrap == WrapMode::Repeat) ? GL_REPEAT : (m_VerticalWrap == WrapMode::MirroredRepeat) ? GL_MIRRORED_REPEAT : (m_VerticalWrap == WrapMode::ClampToEdge) ? GL_CLAMP_TO_EDGE : GL_CLAMP_TO_BORDER;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, vertWrap);
	GLenum horizWrap = (m_HorizontalWrap == WrapMode::Repeat) ? GL_REPEAT : (m_HorizontalWrap == WrapMode::MirroredRepeat) ? GL_MIRRORED_REPEAT : (m_HorizontalWrap == WrapMode::ClampToEdge) ? GL_CLAMP_TO_EDGE : GL_CLAMP_TO_BORDER;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, horizWrap);
	GLenum filterMode = (m_FilterMode == FilterMode::Nearest) ? GL_NEAREST : GL_LINEAR;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);

	GLenum format = (m_Channels == 1) ? GL_RED : (m_Channels == 3) ? GL_RGB : GL_RGBA;

	glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_Data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(m_Data);
}

void Texture::Bind(unsigned int unit) {
	if (unit > GetMaxTextureSlots()) {
		CGFATAL("Texture slot exceeds amount supported by system.");
		return;
	}
	if (!m_ID) Init();
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_ID);
}

const std::string& Texture::GetName() const {
	return m_Name;
}

unsigned int Texture::GetMaxTextureSlots() {
	static int maxTextureSlots;
	if (maxTextureSlots != 0) return maxTextureSlots;
	glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxTextureSlots);
	return maxTextureSlots;
}

void Texture::Register() {
	Engine::RegisterTexture(this);
}
