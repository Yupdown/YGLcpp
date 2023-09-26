#pragma once
#include <string>

namespace ygl
{
	class Scene;

	class YGLFramework
	{
	private:
		static std::string applicationTitle;
		static Scene* currentScene;
		static void (*updateCallback)();

	public:
		static void Initialize(int argc, char** argv);
		static void SetUpdateHandler(void (*callback)());

	private:
		static void Update();
		static void DrawScene();
		static void Reshape(int x, int y);
	};
}