#pragma once
#include "pch.h"

namespace ygl
{
	class Object;
	class ObjectCamera;

	class Scene
	{
	private:
		ObjectCamera* camera;
		std::vector<Object*> objects;

	public:
		Scene(ObjectCamera* camera);
		~Scene();

		void AddObject(Object* obj);
		bool RemoveObject(Object* obj);

		ObjectCamera* GetCamera() const;
		void SetCamera(ObjectCamera* camera);

	public:
		void Redraw();
	};
}
