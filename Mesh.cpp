#include "pch.h"
#include "Mesh.h"

namespace ygl
{
	Mesh::Mesh()
	{
		vao = NULL;
		vbo[0] = NULL;
		vbo[1] = NULL;
		ebo = NULL;

		vertexDirty = false;
		hasObject = false;
	}

	Mesh::~Mesh()
	{
		if (hasObject)
		{
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(2, vbo);
			glDeleteBuffers(1, &ebo);
		}
	}

	void Mesh::LoadFromFile(const char* fileName)
	{
		objl::Loader loader;
		if (!loader.LoadFile(PATH_PREFIX + fileName))
			return;

		for (int i = 0; i < loader.LoadedMeshes.size(); ++i)
		{
			objl::Mesh m = loader.LoadedMeshes[i];

			for (int j = 0; j < m.Vertices.size(); ++j)
			{
				objl::Vector3 p = m.Vertices[j].Position;
				objl::Vector3 n = m.Vertices[j].Normal;
				ygl::Vector3 pp = Vector3(p.X, p.Y, p.Z);
				ygl::Vector3 np = Vector3(n.X, n.Y, n.Z);

				AppendVertex(pp);
				AppendNormal(np);
			}

			for (int j = 0; j < m.Indices.size(); ++j)
			{
				GLuint u = m.Indices[j];
				AppendIndex(u);
			}
		}
	}

	void Mesh::AppendVertex(const Vector3& v)
	{
		positions.push_back(v.x);
		positions.push_back(v.y);
		positions.push_back(v.z);

		vertexDirty = false;
	}

	void Mesh::AppendColor(const Vector3& v)
	{
		colors.push_back(v.x);
		colors.push_back(v.y);
		colors.push_back(v.z);

		vertexDirty = false;
	}

	void Mesh::AppendNormal(const Vector3& v)
	{
		normals.push_back(v.x);
		normals.push_back(v.y);
		normals.push_back(v.z);

		vertexDirty = false;
	}

	void Mesh::AppendUV(const Vector3& v)
	{
		uvs.push_back(v.x);
		uvs.push_back(v.y);

		vertexDirty = false;
	}

	void Mesh::AppendIndex(GLuint v)
	{
		indices.push_back(v);

		vertexDirty = false;
	}

	void Mesh::AppendIndex(GLuint v0, GLuint v1, GLuint v2)
	{
		indices.push_back(v0);
		indices.push_back(v1);
		indices.push_back(v2);

		vertexDirty = false;
	}

	void Mesh::MakeGLObjects()
	{
		glGenVertexArrays(1, &vao);
		glGenBuffers(2, vbo);
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * positions.size(), positions.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colors.size(), colors.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
		glEnableVertexAttribArray(1);

		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

		hasObject = true;
	}

	void Mesh::ValidateGLObjects()
	{
		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * positions.size(), positions.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colors.size(), colors.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

		vertexDirty = true;
	}

	void Mesh::Draw(GLenum mode)
	{
		if (!vertexDirty)
			ValidateGLObjects();
		glBindVertexArray(vao);
		glDrawElements(mode, indices.size(), GL_UNSIGNED_INT, 0);
	}
}