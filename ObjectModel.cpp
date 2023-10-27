#include "pch.h"
#include "ObjectModel.h"
#include "Mesh.h"
#include "Shader.h"

namespace ygl
{
	ObjectModel::ObjectModel() : Object()
	{
		modelMesh = nullptr;
		modelShader = nullptr;
	}

	ObjectModel::~ObjectModel()
	{

	}

	void ObjectModel::OnRedraw()
	{
		modelShader->UseProgram();
		modelShader->SetUniformMatrix4x4("world_Transform", matrixTRSWorld);
		modelMesh->Draw(GL_TRIANGLES);
	}
}