#pragma once
#include "pch.h"

namespace ygl
{
	class Object;

	class Scene
	{
	private:
		std::vector<Object*> objects;

	public:
		Scene();
		~Scene();

	public:
		void Redraw();
	};
}
