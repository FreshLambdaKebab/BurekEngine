#include "Shader.h"

#include "Debug.h"
#include <fstream>
#include <vector>

Shader::Shader() :
	m_numAttributes(0),
	m_programID(0),
	m_vertexShaderID(0),
	m_fragmentShaderID(0)
{
}

Shader::~Shader()
{
}

void Shader::Compile(const std::string & vertexShaderFilePath, const std::string & fragmentShaderFilePath)
{
	m_programID = glCreateProgram();

	//create the vertex shader
	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (m_vertexShaderID == 0)
	{
		FatalError("Vertex shader failed to create!");
	}

	//create the fragment shader
	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (m_fragmentShaderID == 0)
	{
		FatalError("Fragment shader failed to create!");
	}
	
	//compile each shader
	CompileShader(vertexShaderFilePath, m_vertexShaderID);
	CompileShader(fragmentShaderFilePath, m_fragmentShaderID);
	
}

void Shader::LinkShaders()
{
	//Attach our shaders to our program
	glAttachShader(m_programID, m_vertexShaderID);
	glAttachShader(m_programID, m_fragmentShaderID);

	//Link our program
	glLinkProgram(m_programID);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<char> errorLog(maxLength);
		glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(m_programID);
		//Don't leak shaders either.
		glDeleteShader(m_vertexShaderID);
		glDeleteShader(m_fragmentShaderID);

		//print the error log and quit
		std::printf("%s\n", &(errorLog[0]));
		FatalError("Shaders failed to link!");
	}

	//Always detach shaders after a successful link.
	glDetachShader(m_programID, m_vertexShaderID);
	glDetachShader(m_programID, m_fragmentShaderID);
	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);
}

void Shader::AddAttribute(const std::string & attribName)
{
	glBindAttribLocation(m_programID, m_numAttributes++, attribName.c_str());
}

void Shader::Use()
{
	glUseProgram(m_programID);
	for (int i = 0; i < m_numAttributes; i++) 
	{
		glEnableVertexAttribArray(i);
	}
}

void Shader::Unuse()
{
	glUseProgram(0);
	for (int i = 0; i < m_numAttributes; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void Shader::CompileShader(const std::string & filePath, GLuint& id)
{
	//create the vertex shader
	std::ifstream shaderFile(filePath);
	if (shaderFile.fail())
	{
		perror(filePath.c_str());
		FatalError("Failed to open " + filePath);
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(shaderFile, line))
	{
		fileContents += line + "\n";
	}

	shaderFile.close();

	const char* pContents = fileContents.c_str();
	glShaderSource(id, 1, &pContents, nullptr);

	glCompileShader(id);

	//create the fragment shader
	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);

		printf("%s\n", &errorLog[0]);
		FatalError("Shader " + filePath + " failed to compile!");
	}
}
