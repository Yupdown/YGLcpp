#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "ObjectCameraOrthographic.h"
#include "ObjectCameraPerspective.h"

namespace ygl
{
	Scene::Scene(ObjectCamera* camera)
	{
		SetCamera(camera);
	}

	Scene::~Scene()
	{

	}

	void Scene::AddObject(Object* obj)
	{
		objects.push_back(obj);
	}

	bool Scene::RemoveObject(Object* obj)
	{
		auto iter = std::find(objects.begin(), objects.end(), obj);
		if (iter == objects.end())
			return false;
		objects.erase(iter);
		return true;
	}

	ObjectCamera* Scene::GetCamera() const
	{
		return camera;
	}

	void Scene::SetCamera(ObjectCamera* camera)
	{
		if (this->camera != nullptr)
			RemoveObject(this->camera);
		this->camera = camera;
		AddObject(camera);
	}

	void Scene::Redraw()
	{
		camera->BeginDraw();
		for (Object* obj : objects)
			obj->Redraw(false);
	}
}