#include "pch.h"
#include "Scene.h"
#include "Object.h"

namespace ygl
{
	Scene::Scene()
	{

	}

	Scene::~Scene()
	{

	}

	void Scene::Redraw()
	{
		for (Object* obj : objects)
			obj->Redraw();
	}
}