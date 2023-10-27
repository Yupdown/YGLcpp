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

	void ObjectModel::OnRedraw()
	{
		modelShader->UseProgram();
		modelShader->SetUniformMatrix4x4("model_Transform", matrixTRSWorld);
		modelMesh->Draw(GL_TRIANGLES);
	}
}