#pragma once
#include "Object.h"

namespace ygl
{
	class Mesh;
	class Shader;

	class ObjectModel : public Object
	{
	private:
		Mesh*	modelMesh;
		Shader*	modelShader;

	public:
		ObjectModel(Mesh* mesh, Shader* shader);
		virtual ~ObjectModel() override;

	public:
		Mesh* GetMesh() const;
		Shader* GetShader() const;

	public:
		void SetMesh(Mesh* mesh);
		void SetShader(Shader* shader);

	protected:
		virtual void OnRedraw() override;
	};
}