#pragma once
#include "pch.h"
#include "OBJ_Loader.h"

namespace ygl
{
	class Mesh
	{
	private:
		const string PATH_PREFIX = "resource/mesh/";

	private:
		vector<GLfloat> positions;
		vector<GLfloat> colors;
		vector<GLfloat> normals;
		vector<GLfloat> uvs;
		vector<GLuint>	indices;

		GLuint vao;
		GLuint vbo[2];
		GLuint ebo;

		bool vertexDirty;
		bool hasObject;

	public:
		Mesh();
		~Mesh();

		GLvoid LoadFromFile(const char* fileName);
		void AppendVertex(const Vector3& v);
		void AppendColor(const Vector3& v);
		void AppendNormal(const Vector3& v);
		void AppendUV(const Vector3& v);
		void AppendIndex(GLuint v);
		void AppendIndex(GLuint v0, GLuint v1, GLuint v2);

		void MakeGLObjects();
		void ValidateGLObjects();

		void Draw(GLenum mode);
	};
}