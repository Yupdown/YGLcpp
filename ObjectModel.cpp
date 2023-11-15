#include "pch.h"
#include "ObjectModel.h"
#include "Mesh.h"
#include "Shader.h"

namespace ygl
{
	ObjectModel::ObjectModel(Mesh* mesh, Shader* shader)
	{
		modelMesh = mesh;
		modelShader = shader;
	}

	ObjectModel::~ObjectModel()
	{
		modelMesh = nullptr;
		modelShader = nullptr;
	}

	Mesh* ObjectModel::GetMesh() const
	{
		return modelMesh;
	}

	Shader* ObjectModel::GetShader() const
	{
		return modelShader;
	}

	void ObjectModel::SetMesh(Mesh* mesh)
	{
		modelMesh = mesh;
	}

	void ObjectModel::SetShader(Shader* shader)
	{
		modelShader = shader;
	}

	void ObjectModel::OnRedraw()
	{
		modelShader->UseProgram();
		modelShader->SetUniformMatrix4x4("model_Transform", matrixTRSWorld);
		modelMesh->Draw(GL_TRIANGLES);
	}
}