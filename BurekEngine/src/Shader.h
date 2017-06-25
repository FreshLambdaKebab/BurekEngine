#ifndef _SHADER_H
#define _SHADER_H

#include <GL\glew.h>
#include <string>

class Shader
{
public:
	Shader();
	~Shader();

	//compile shader from given path
	void Compile(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	void LinkShaders();

	void AddAttribute(const std::string& attribName);

	void Use();
	void Unuse();

	GLuint GetUniformLocation(const std::string& uniformName)const;

private:
	void CompileShader(const std::string& filePath, GLuint& id);

	int m_numAttributes;

	GLuint m_programID;
	GLuint m_vertexShaderID;
	GLuint m_fragmentShaderID;

};

#endif //_SHADER_H
