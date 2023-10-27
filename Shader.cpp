#include "pch.h"
#include "Shader.h"

char* FileToBuffer(const char* file);

namespace ygl
{
	Shader::Shader(const char* vertFile, const char* fragFile)
	{
		shaderVertexID = MakeShaders(vertFile, GL_VERTEX_SHADER);
		shaderFragmentID = MakeShaders(fragFile, GL_FRAGMENT_SHADER);
		MakeShaderProgram(shaderVertexID, shaderFragmentID);
	}

	Shader::~Shader()
	{
		glDeleteProgram(programID);
		glDeleteShader(shaderVertexID);
		glDeleteShader(shaderFragmentID);
	}

	void Shader::UseProgram()
	{
		glUseProgram(programID);
	}

	void Shader::SetUniformFloat(const char* key, float value)
	{
		unsigned int modelLocation = glGetUniformLocation(programID, key);
		glUniform1f(modelLocation, value);
	}

	void Shader::SetUniformVector2(const char* key, const Vector2& value)
	{
		unsigned int modelLocation = glGetUniformLocation(programID, key);
		glUniform2fv(modelLocation, 1, glm::value_ptr(value));
	}

	void Shader::SetUniformVector3(const char* key, const Vector3& value)
	{
		unsigned int modelLocation = glGetUniformLocation(programID, key);
		glUniform3fv(modelLocation, 1, glm::value_ptr(value));
	}

	void Shader::SetUniformVector4(const char* key, const Vector4& value)
	{
		unsigned int modelLocation = glGetUniformLocation(programID, key);
		glUniform4fv(modelLocation, 1, glm::value_ptr(value));
	}

	void Shader::SetUniformMatrix4x4(const char* key, const Matrix4x4& value)
	{
		unsigned int modelLocation = glGetUniformLocation(programID, key);
		glUniformMatrix4fv(modelLocation, 1, false, glm::value_ptr(value));
	}

	GLuint Shader::MakeShaders(const char* fileName, GLenum shaderType)
	{
		GLchar* src = FileToBuffer((PATH_PREFIX + fileName).c_str());
		GLuint shaderID = glCreateShader(shaderType);

		glShaderSource(shaderID, 1, &src, NULL);
		glCompileShader(shaderID);

		GLint result;
		GLchar errorLog[512];

		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(shaderID, 512, NULL, errorLog);
			std::cerr << "ERROR: shader compile FAILED\n" << errorLog << std::endl;
		}
		return shaderID;
	}

	void Shader::MakeShaderProgram(GLuint vertShader, GLuint fragShader)
	{
		programID = glCreateProgram();

		glAttachShader(programID, vertShader);
		glAttachShader(programID, fragShader);

		glLinkProgram(programID);

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);

		GLint result;
		GLchar errorLog[512];

		glGetProgramiv(programID, GL_LINK_STATUS, &result);
		if (!result)
		{
			glGetShaderInfoLog(programID, 512, NULL, errorLog);
			std::cerr << "ERROR: shader program link FAILED\n" << errorLog << std::endl;
		}
	}
}

char* FileToBuffer(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;

	fopen_s(&fptr, file, "rb");			// Open file for reading
	if (!fptr)							// Return NULL on failure
		return NULL;

	fseek(fptr, 0, SEEK_END);			// Seek to the end of the file
	length = ftell(fptr);				// Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1);	// Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET);			// Go back to the beginning of the file
	fread(buf, length, 1, fptr);		// Read the contents of the file in to the buffer

	fclose(fptr);						// Close the file
	buf[length] = 0;					// Null terminator

	return buf;							// Return the buffer
}